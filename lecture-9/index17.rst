Другие библиотеки
=================

Utility
-------

* `boost/ <https://www.boost.org/libs/utility>`_
* ``boost::checked_delete()`` и ``boost::checked_array_delete()`` делают аналогичную работу за ``delete`` и ``delete[]``
  * Функции убеждаются, что тип полный (complete)
* Макрос ``BOOST_CURRENT_FUNCTION`` выдаёт имя текущей функции
  * В C++11 есть аналог ``__func__``
* ``boost::prior()`` и ``boost::next()`` аналогичные ``std::prev`` и ``std::next``
* Наследуясь от ``boost::noncopyable`` автоматически убирает все порождающие операторы копирования
* ``boost::addressof()`` позволяет получить адрес объекта, даже если ``operator&`` перегружен
  * Аналогично ``std::addressof``
* ``BOOST_BINARY(1001 0001)`` позволяет создавать константы в двоичном формате
  * В C++17 появился префикс ``0b``
* ``boost::string_ref`` аналогично ``std::string_view``

Assign
------

* `boost/assign.hpp <https://www.boost.org/libs/assign>`_
* Инициализация контейнера с помощью ``list_of``, ``map_list_of`` и т.д.
  * Есть более современный метод через ``std::initializer_list``
* Более простой способ добавляеть элементы в контейнер
  * Поддержка методами ``push_back``, ``push_front``, ``insert`` и ``push``
* Добавление элементов через оператор ``,``

.. code:: cpp

    std::vector<std::pair<std::string, int>> v = boost::assign::list_of<std::pair<std::string, int>>("a", 1)("b", 2)("c", 3);

    std::vector<int> v2;
    boost::assign::push_back(v2)(1)(2)(3);

    using namespace boost::assign;

    vector<int> values;
    values += 1,2,3,4,5,6,7,8,9;

Операторы
---------

* `boost/operators.hpp <https://www.boost.org/libs/utility/operators.htm>`_
* Вспомогательные для наследования классы с предопределёнными операторами
* При наследовании от ``boost::less_than_comparable`` достаточно определить лишь ``operator<``
* Множество других классов для наследования с различными комбинациями
* Возможно определять итераторы

.. code:: cpp

    class MyInt : boost::operators<MyInt>
    {
        bool operator<(const MyInt& x) const;
        bool operator==(const MyInt& x) const;
        MyInt& operator+=(const MyInt& x);
        MyInt& operator-=(const MyInt& x);
        MyInt& operator*=(const MyInt& x);
        MyInt& operator/=(const MyInt& x);
        MyInt& operator%=(const MyInt& x);
        MyInt& operator|=(const MyInt& x);
        MyInt& operator&=(const MyInt& x);
        MyInt& operator^=(const MyInt& x);
        MyInt& operator++();
        MyInt& operator--();
    };
