Обобщённое программирование
===========================

Type traits
-----------

* `boost/type_traits.hpp <https://www.boost.org/libs/type_traits>`_
* Появилось в C++11
* ``is_integral``, ``is_arithmetic``, ``is_same``, ...
* Метатипы ``true_type``, ``false_type``
* ``has_plus``, ``has_pre_increment``, ``add_rvalue_reference``, ...

* `boost/utility/enable_if.hpp <https://www.boost.org/libs/utility/enable_if.html>`_
* Уже есть в C++11
* Устарел в C++17, так как появился ``constexpr``

Fusion
------

* `boost/ <https://www.boost.org/libs/fusion>`_
* Предоставляет гетерогенные контейнеры (типы элементов разные)
* Похож на boost::mpl, но предоставляет работу со значениями
* Алгоритмы для работы с гетерогенными контейнерами
* ``boost::fusion::vector`` аналогичен ``boost::fusion::tuple``, который аналогичен простому ``tuple``
* В ``fusion::map`` ключами являются типы, значения могут принимать любой тип
* При изменении контейнера всегда создаётся новый, например

  .. code:: cpp

    using namespace boost::fusion;

    vector<int, std::string, bool, double> v{10, "Boost", true, 3.14};
    auto v2 = push_back(v, 'X');
    std::cout << at<boost::mpl::int_<4>>(v2) << std::endl;
* Чтобы использовать алгоритмы из fusion для своих структур, следует воспользоваться ``BOOST_FUSION_ADAPT_STRUCT``

.. code:: cpp

    auto m = make_map<uint8_t, uint16_t, uint32_t>("Boost", 10, 3.14);
    if (has_key<uint16_t>(m))
        std::cout << at_key<uint16_t>(m) << std::endl;
