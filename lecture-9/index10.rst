Параллельное программирование
=============================

Потоки
------

* `boost/thread/ <https://www.boost.org/libs/thread>`_
* Практически ничем не отличается от ``std::thread``, кроме
  * Наличие удобного механизма завершения потока ``boost::scoped_thread``
  * Метод ``interrupt()``, который позволяет остановить выполнение потока
    * Работает только в определённых точках прерывания
    * Прерывание потока не способно остановить бесконечных циклов
  * Тип ``boost::this_thread::disable_interruption`` предотвращает создание точек прерывания
  * Передача ``boost::thread::attributes`` в конструкторе потока позволяет настраивать запуск потока
* ``boost::thread_group`` служит для одновременном запуске нескольких потоков

* Мьютексы, локи и условные переменные эквивалентны STL-версии

* ``boost::thread_specific_ptr`` для компиляторов, не поддерживающих ``thread_local`` из C++11

  .. code:: cpp

    std::mutex mutex;

    auto worker = [&mutex]() {
        static boost::thread_specific_ptr<bool> tls;
        if (!tls.get())
        {
            tls.reset(new bool{true});
            std::lock_guard lock{mutex};
            std::cout << "done" << '\n';
        }
    };

    std::thread t[] = {std::thread{worker}, std::thread{worker}, std::thread{worker}};
    for (auto& x : t)
        x.join();

* ``future``, ``promise``, ``async``, ``packaged_task`` были взяты в STL

Atomic
------

* `boost/atomic.hpp <https://www.boost.org/libs/atomic>`_
* Вошло в С++11
* Гарантирует атомарность записи/чтения типа
* Если процессор не может поддержать атомарность, используется лок
* Различные порядки обращения к памяти
  * ``memory_order_seq_cst`` строгая последовательность (используется по умолчанию)
  * ``memory_order_relaxed`` разрешает любые переупорядочивания команд
  * ``memory_order_release`` разрешает выполнение команд в коде строго до этой команды в конвейере
  * ``memory_order_acquire`` разрешает выполнение команд в коде строго после этой команды в конвейере
  * В STL существуют дополнительные порядки обращения

Lockfree
--------

* `boost/lockfree/ <https://www.boost.org/libs/lockfree>`_
* Предоставляет неблокирующие очереди без необходимости синхронизации
* ``spsc_queue`` --- single producer, single consumer
  * Максимальное количество элементов передаётся либо в конструкторе, либо через шаблонный параметр ``capacity<num>``
* ``queue`` --- multiple producer, multiple consumer
* ``stack``
* Политики очередей
  * ``capacity`` задаёт размер очереди
  * ``fixed_sized`` устанавливает политику фиксированной по размеру очереди
  * ``allocator`` позволяет использовать свой аллокатор
* Есть стандартные методы ``push`` и ``pop``
* Дополнительные методы ``consume_one`` и ``consume_all``

.. code:: cpp

    boost::lockfree::queue<int> q;
    std::atomic<int> sum = 0;

    auto produce = [&q]() {
        for (int i = 1; i <= 100; ++i)
            q.push(i);
    };

    auto consume = [&q](auto& x) {
        while (q.consume_one([](int i){ x += i; }));
    };

    std::thread t1{produce};
    std::thread t2{consume};
    std::thread t3{consume};
    t1.join();
    t2.join();
    t3.join();
    q.consume_all([&sum](int i){ sum += i; });

    std::cout << sum << std::endl;

MPI
---

* `boost/mpi.hpp <https://www.boost.org/libs/mpi>`_
* Напоминает работу с сокетами
* ``boost::mpi::environment`` нужен для запуска MPI, есть только конструктор
* Коммуникатор ``boost::mpi::communicator``
  * Методы ``recv``, ``send`` позволяют обмениваться сообщениями
    * Идентификатор процесса
    * Тэг сообщения
    * Данные
  * Методы ``irecv``, ``isend`` аналогичны предыдущим, но неблокирующие
    * Возвращают объект ``boost::mpi::request``
    * Есть возможность отменить запрос, если оппонент использует блокирующую операцию
    * Функции ``wait_all``, ``wait_any`` и ``wait_some`` для блокирования
  * Метод ``rank()`` для определения своего идентификатора
* ``boost::mpi::any_source`` для принятия сообщения от любого процесса
* В сообщениях можно использовать тип, который поддерживает boost-сериализацию
* ``gather`` позволяет собрать данные со всех процессоров в одном месте
* ``scatter`` раздаёт данные процессам из вектора
* ``broadcast`` раздаёт одинаковые данные всем процессам
* ``reduce`` аналогично ``gather``, но аккумулирует данные через функцию, а не вектор
* ``reduce_all`` аналогично ``reduce``, но результат будет доступен всем процессам
* С помощью функций ``split`` и ``group`` можно формировать своё подмножество процессов

.. code:: cpp

    boost::mpi::environment env{argc, argv};
    boost::mpi::communicator world;

    std::string s;
    if (world.rank() == 0)
        s = "Hello, world!";
    else if (world.rank() == 1)
        s = "Hello, moon!";
    else if (world.rank() == 2)
        s = "Hello, sun!";

    std::string result;
    boost::mpi::reduce(world, s, result, std::min<std::string>, 0);
    if (world.rank() == 0)
        std::cout << result << std::endl;
