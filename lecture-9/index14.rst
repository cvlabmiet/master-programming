Работа с числами
================

Аккумуляторы
------------

* `boost/accumulators/ <https://www.boost.org/libs/accumulators>`_
* Доступ к различным аккумуляторам, в том числе статистическим
* ``accumulator_set`` для создания аккумулятора по тэгу
* Различные статистики
* Умеет работать с ``std::complex``, ``std::valarray``, ``std::vector`` и примитивными типами
* Экстракторы ``count``, ``mean``, ``variance``, ``moment<N>`` нужны для получения итогового значения

.. code:: cpp

    using namespace boost::accumulators;

    accumulator_set<double, features<tag::mean, tag::variance>, int> acc;
    acc(8, weight = 1);
    acc(9, weight = 1);
    acc(10, weight = 4);
    acc(11, weight = 1);
    acc(12, weight = 1);
    std::cout << mean(acc) << ":" << variance(acc) << std::endl;

Преобразование чисел
--------------------

* `boost/numeric/conversion/ <https://www.boost.org/libs/numeric/conversion>`_
* ``boost::numeric_cast`` позволяет производить преобразование числа в разные типы
* Генерируется исключение, если число не помещается в заданный тип
* Существуют исключения ``positive_overflow``, ``negative_overflow``, ...
* Класс ``boost::numeric::converter`` позволяет создавать конвертеры более детально
* Класс ``bounds`` служит для определения границ числа, соответствует ``std::numeric_limits``
* Можно написать свои политики перехвата переполнения, округления

.. code:: cpp

    try
    {
        int i = 0x10000;
        short s = boost::numeric_cast<short>(i);
        std::cout << s << std::endl;
    }
    catch (boost::numeric::bad_numeric_cast &e)
    {
        std::cerr << e.what() << std::endl;
    }

Что уже вошло в STL
-------------------

* `boost/cstdint.hpp <https://www.boost.org/libs/integer>`_ == ``cstdint``
* `boost/minmax.hpp <https://www.boost.org/libs/algorithm/minmax>`_ == ``std::minmax``, ``std::minmax_element``
* `boost/random.hpp <https://www.boost.org/libs/random>`_ == ``random``
