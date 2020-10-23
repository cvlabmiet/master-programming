Потоки ввода/вывода и файлы
===========================

Потоки ввода/вывода
-------------------

* `boost/iostreams/ <https://www.boost.org/libs/iostreams>`_
* **Устройство** представляет из себя класс, у которого есть методы ``read`` и ``write``
  * sink и source для определения типа устройства
  * ``array_sink``, ``array_source`` предоставляют в качестве устройств массивы
  * Существуют адапторы, наподобие ``back_insert_device``
  * ``file_sink`` и ``file_source`` для работы с файлами
  * ``mapped_file_source`` и ``mapped_file_sink`` для работы с файлами в памяти
  * ``file_descriptor_source`` и ``file_descriptor_sink`` для работы с нативными дескрипторами
* Создание потока ввода/вывода осуществляется через класс ``stream``

.. code:: cpp

    using namespace boost::iostreams;

    std::vector<char> v;
    back_insert_device<std::vector<char>> sink{v};
    stream os{sink};
    os << "Boost" << std::endl;

    file_source f{"text.txt"};
    if (f.is_open())
    {
        stream is{f};
        std::cout << is.rdbuf() << std::endl;
    }

Фильтры потока ввода/вывода
---------------------------

* Фильтры позволяют манипулировать данные в потоке
* ``filtering_istream`` и ``filtering_ostream``
* Имеют интерфейсы потока и списка
* Некоторые фильтры кешируемые, поэтому данные будут обработаны после освобождения устройства
* Последним фильтром всегда должно быть устройство
* Порядок вставки фильтров важен

.. code:: cpp

    std::vector<char> v;
    back_insert_device<std::vector<char>> snk{v};
    filtering_ostream os;
    os.push(zlib_compressor{});
    os.push(snk);
    os << "Boost" << std::flush;
    os.pop();

    array_source src{v.data(), v.size()};
    filtering_istream is;
    is.push(zlib_decompressor{});
    is.push(counter{});
    is.push(src);
    std::string s;
    is >> s;

    counter *c = os.component<counter>(0);
    std::cout << s << "\n"
              << "Stats: characters = " << c->characters() << " lines = " << c->lines() << std::endl;

Работа с файловой системой
--------------------------

* `boost/filesystem/ <https://www.boost.org/libs/filesystem>`_
* Принято в C++17
* ``boost::filesystem::path`` позволяет описывать пути, является основным для работы типом
* Различные функции для работы с файлами и директориями
* Итераторы для обхода директорий
* Потоки ввода/вывода умеют работать с ``filesystem::path``
