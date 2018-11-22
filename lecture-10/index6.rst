Межпроцессорное взаимодействие
==============================

Asio
----

* `boost/ <https://www.boost.org/libs/asio>`_
* Синхронные и асинхронные операции с сетевым оборудованием
  * Асинхронность работает благодаря сервисному объекту ``io_service``
* Умеет работать с объектами ввода/вывода
  * Таймеры ``steady_timer``
  * Сетевые объекты ``ip::tcp::socket``, ``ip::tcp::iostream``, ``ip::udp``
  * Портами последовательного доступа ``serial_port`` (USB, UART, ...)
* Масштабируемость --- ``std::thread thread1{[&ioservice](){ ioservice.run(); }};``
* Основано на IOCP (Windows) и epoll (Linux), есть доступ к платформозависимым низкоуровневым объектам

.. code:: cpp

    using namespace std::literals;

    io_service ioservice;

    steady_timer timer1{ioservice, 3s};
    timer1.async_wait([](auto) { std::cout << "3 sec\n"; });

    steady_timer timer2{ioservice, 4s};
    timer2.async_wait([](auto) { std::cout << "4 sec\n"; });

    ioservice.run();

Работа с сетью в boost::asio
----------------------------

* Уровень IP, асинхронный

  .. code:: cpp

    io_service ioservice;
    ip::tcp::endpoint tcp_endpoint{ip::tcp::v4(), 2018};
    ip::tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
    ip::tcp::socket tcp_socket{ioservice};
    std::string data;

    tcp_acceptor.listen();
    tcp_acceptor.async_accept(tcp_socket, [&data, &tcp_socket](const boost::system::error_code& ec) {
        if (!ec)
        {
            data = "tra-la-la";
            async_write(tcp_socket, buffer(data), [](const boost::system::error_code& ec, size_t bytes) {
                if (!ec)
                    tcp_socket.shutdown(tcp::socket::shutdown_send);
            });
        }
    });

    ioservice.run();

* Уровень стрима, синхронный

  .. code:: cpp

    boost::asio::ip::tcp::iostream s("www.boost.org", "http");
    s.expires_from_now(std::chrono::seconds(60));

    s << "GET /LICENSE_1_0.txt HTTP/1.0\r\n"
    s << "Host: www.boost.org\r\n";
    s << "Accept: */*\r\n";
    s << "Connection: close\r\n\r\n" << std::flush;

    std::string header;
    while (std::getline(s, header) && header != "\r")
        std::cout << "HEAD: " << header << std::endl;

    std::cout << "BODY: " << s.rdbuf();

* Использование Coroutine подхода

  .. code:: cpp

    io_service ioservice;
    ip::tcp::endpoint tcp_endpoint{ip::tcp::v4(), 2018};
    ip::tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
    std::list<ip::tcp::socket> tcp_sockets;

    auto do_write = [](tcp::socket &tcp_socket, yield_context yield)
    {
      std::string data = "u-la-la";
      async_write(tcp_socket, buffer(data), yield);
      tcp_socket.shutdown(tcp::socket::shutdown_send);
    }

    auto do_accept = [&tcp_sockets, &ioservice, &tcp_acceptor, do_write](yield_context yield)
    {
        for (int i = 0; i < 2; ++i)
        {
            tcp_sockets.emplace_back(ioservice);
            tcp_acceptor.async_accept(tcp_sockets.back(), yield);
            spawn(ioservice, [](yield_context yield) { do_write(tcp_sockets.back(), yield); });
        }
    }

    tcp_acceptor.listen();
    spawn(ioservice, do_accept);
    ioservice.run();

Разделяемая память
------------------

* `boost/interprocess/ <http://www.boost.org/libs/interprocess>`_
* ``shared_memory_object`` создаёт/открывает разделяемую память по имени на чтение/запись
* Для работы с адресами разделяемой памяти необходимо использовать ``mapped_region``
* Что освободить ресурсы памяти, необходимо явно вызывать ``shared_memory_object::remove``
  * RAII поддерживается благодаря ``remove_shared_memory_on_destroy``

.. code:: cpp

    shared_memory_object shdmem{open_or_create, "Boost", read_write};
    shdmem.truncate(1024);
    mapped_region region{shdmem, read_write};
    int *i1 = static_cast<int*>(region.get_address());
    *i1 = 99;
    mapped_region region2{shdmem, read_only};
    int *i2 = static_cast<int*>(region2.get_address());
    std::cout << *i2 << std::endl;

Управляемая разделяемая память
------------------------------

* Создание объектов внутри разделяемой памяти
* Именованные объекты
* Поддержка стандартных контейнеров (нестандартным аллокатором)
* Создание массивов объектов
* Исключения в случае нехватки памяти
* Возможность создавать несколько объектов атомарно

.. code:: cpp

    shared_memory_object::remove("Boost");
    managed_shared_memory managed_shm{open_or_create, "Boost", 1024};

    int *i = managed_shm.construct<int>("Integer")[10](99);
    std::cout << *i << "\n";

    std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
    if (p.first)
        std::cout << *p.first << ":" << p.second << "\n";

    using char_allocator = boost::allocator<char, managed_shared_memory::segment_manager>;
    using string = boost::basic_string<char, std::char_traits<char>, char_allocator> string;
    string* s = managed_shm.find_or_construct<string>("String")("Hello!", managed_shm.get_segment_manager());
    s->insert(5, ", world");
    std::cout << *s << std::endl;

    managed_shm.destroy<int>("Integer");

Разделяемые объекты синхронизации
---------------------------------

* ``boost/interprocess/sync/``
* Именованные мьютексы (не требуют разделяемой памяти) ``named_mutex``
* Анонимные мьютексы (создаются внутри разделяемой памяти) ``interprocess_mutex``
* Поддерживаются рекурсивные версии мьютексов ``named_recursive_mutex`` и ``interprocess_recursive_mutex``
* Именованные условные переменные ``named_condition``
* Анонимные условные переменные ``interprocess_condition``

.. code:: cpp

    managed_shared_memory managed_shm{open_or_create, "shm", 1024};
    int *i = managed_shm.find_or_construct<int>("Integer")(0);
    interprocess_mutex *mtx = managed_shm.find_or_construct<interprocess_mutex>("mtx")();
    named_condition named_cnd{open_or_create, "cnd"};
    std::lock_guard lock{*mtx};
    while (*i < 10)
    {
        if (*i % 2 == 0)
        {
            ++(*i);
            cnd->notify_all();
            cnd->wait(lock);
        }
        else
        {
          std::cout << *i << std::endl;
          ++(*i);
          cnd->notify_all();
          cnd->wait(lock);
        }
    }
    cnd->notify_all();
    shared_memory_object::remove("shm");
