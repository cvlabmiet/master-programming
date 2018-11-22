Работа со временем
==================

Календарь
---------

* `boost/date_time/ <https://www.boost.org/libs/date_time>`_
* ``boost::gregorian::date`` для работы с календарём
* Класс ``boost::gregorian::day_clock`` для получения текущей даты
  * Статические методы ``universal_day()`` и ``local_day()``
* Функция ``date_from_iso_string()`` служит для преобразования ISO-форматированной строки в объект ``date``
* Класс ``date_duration`` нужен для произведения вычислений с датой
* Класс ``date_period`` нужен для поддержания диапазона времени
  * Метод ``contains`` позволяет узнавать принадлежность даты какому-то периоду
* ``day_iterator``, ``week_iterator``, ... --- итератор, позволяет итерироваться по датам

.. code:: cpp

    using namespace boost::gregorian;

    date d{2018, 11, 19};
    months ms{1};
    date d2 = d + ms;
    date d3 = d2 - ms;
    std::cout << d2 << " vs. " << d3 << std::endl;

Добавление времени к календарю
------------------------------

* Пространство имён ``posix_time`` даёт возможность манипулировать временем
* Для создания, необходима календарная дата
* Поддерживаются те же принципы: ``time_duration``, ``time_period``
* Для поддержания локального времени (таймзона) следует использовать пространство имён ``local_time``

.. code:: cpp

    using namespace boost::posix_time;
    using namespace boost::gregorian;

    ptime pt{date{2014, 5, 12}, time_duration{12, 0, 0}};
    time_iterator it{pt, time_duration{6, 30, 0}};
    std::cout << *++it << "\n" << *++it << std::endl;

Chrono
------

* `boost/chrono.hpp <http://www.boost.org/libs/chrono>`_
* Вошло в C++11
* Различные клоки
  * ``steady_clock`` возвращает монотонное время
  * ``system_clock`` возвращает текущее время, чувствительно к переводу часов
  * ``high_resolution_clock`` предоставляет самый точный хронометраж в системе
  * ``process_real_cpu_clock`` возвращает время с момента старта программы
  * ``process_user_cpu_clock`` возвращает затраченное время в пользовательском пространстве
  * ``process_system_cpu_clock`` возвращает затраченное время в режиме ядра
  * ``process_cpu_clock`` возвращает кортеж из затраченных времён
  * ``thread_clock`` работает как ``steady_clock``, но для потока
* Можно выводить время в поток с помощью ``chrono_io.hpp``
* Арифметика времени и кастование

.. code:: cpp

    using namespace boost::chrono;

    process_real_cpu_clock::time_point p = process_real_cpu_clock::now();
    std::cout << p << "\n" << time_point_cast<minutes>(p) << std::endl;

Таймер
------

* `boost/timer/timer.hpp <https://www.boost.org/libs/timer>`_
* ``cpu_timer`` для автоматической замеры времени
  * ``start()`` позволяет перезапускать таймер, конструктор делает это автоматически
  * ``stop()``, ``resume()`` для временной остановки таймера
  * ``fromat()`` выводит всю информацию по пройденному времени
  * ``elapsed()`` возвращает структуру с временными метриками
    * ``wall``, ``user``, ``system`` --- полное время, время в пространстве пользователя и ядра
* ``auto_cpu_timer`` в деструкторе делает ``std::cout << timer.format()``

.. code:: cpp

    boost::timer::auto_cpu_timer timer;

    for (int i = 0; i < 1000000; ++i)
        std::pow(1.234, i);
