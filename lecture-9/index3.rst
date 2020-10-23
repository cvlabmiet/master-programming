Контейнеры
==========

Мульти-индекс
-------------

* `boost/multi_index/ <https://www.boost.org/libs/multi_index>`_
* Позволяет реализовать контейнер с несколькими интерфейсами
* Ключи-экстракторы ``member``, ``const_mem_fun`` (``mem_fun``), ``identity``, ``global_fun``, ``composite_key``
* Изменять значения в контейнере можно только через функцию ``modify``
* Используется метод ``get`` для получения конкретного интерфейса
* Контейнер должен удовлетворять условиям всех интерфейсов

.. class:: column50

    .. code:: cpp

        struct animal
        {
            std::string name;
            int legs;
        };

        boost::multi_index::multi_index_container<
            animal,
            boost::multi_index::indexed_by<
                boost::multi_index::sequenced<>,
                boost::multi_index::ordered_non_unique<
                    boost::multi_index::member<
                        animal, std::string, &animal::name
                    >
                >,
                boost::multi_index::random_access<>
            >
        > animals;

        animals.emplace_back("cat", 4);
        animals.emplace_back("shark", 0);
        animals.emplace_back("spider", 8);

        auto& legs_index = animals.get<1>();
        auto it = legs_index.find(4);
        legs_index.modify(it, [](animal &a){ a.name = "dog"; });

.. class:: column50

    .. list-table:: Основные интерфейсы и их совместимый тип

        - * ``sequenced``
          * ``std::list``
        - * ``hashed_unique``
          * ``std::unordered_set``
        - * ``hashed_non_unique``
          * ``std::unordered_multiset``
        - * ``ordered_non_unique``
          * ``std::multiset``
        - * ``ordered_unique``
          * ``std::set``
        - * ``random_access``
          * ``std::vector``

Bimap
-----

* `boost/bimap.hpp <https://www.boost.org/libs/bimap>`_
* Ассоциативный массив, в котором значения также являются ключами
* Основан на ``boost::multi_index_container``
* Предоставляет ссылки ``left`` и ``right`` для получения интерфейса ``std::set``
* Не позволяет использовать одинаковые ключи, поэтому вводятся специальные структуры
  * ``boost::bimaps::set_of`` используется по умолчанию
  * ``boost::bimaps::multiset_of`` используется для неуникальных значений
  * ``boost::bimaps::list_of``, ``boost::bimaps::vector_of``, ``boost::bimaps::unconstrained_set_of``, ...
* Модификаторы ``boost::bimaps::_key`` и ``boost::bimaps::_data``

.. code:: cpp

    boost::bimap<std::string, boost::bimaps::unconstrained_set_of<int>> animals;

    animals.insert({"cat", 4});
    animals.insert({"shark", 0});
    animals.insert({"spider", 8});

    auto it = animals.left.find("cat");
    animals.left.modify_key(it, boost::bimaps::_key = "dog");

Array
-----

* `boost/array.hpp <https://www.boost.org/libs/array>`_
* Массив на стеке, количество элементов необходимо задавать руками
* Обвязка над стандартными массивами, например, ``int a[42]``
* Полностью аналогичен ``std::array``

Неупорядоченные (ассоциативные) массивы
---------------------------------------

* `boost/unordered_*.hpp <https://www.boost.org/libs/unordered>`_
* Данные внутри массивов не обладают порядком, так как используется хэш
* Для помещаемых данных необходимо наличие перегруженных ``operator==`` и ``hash_value``
* Полностью эквивалентно ``std::unordered_set/multiset`` и ``std::unordered_map/multimap``

Циклический буфер
-----------------

* `boost/circular_buffer.hpp <https://www.boost.org/libs/circular_buffer>`_
* Контейнер с интерфейсом ``std::vector``
* Описывается с помощью двух массивов: головы и хвоста
* API
  * ``is_linearized`` --- можно ли буфер представить только одним массивом
  * ``array_one``, ``array_two`` --- голова и хвост буфера
  * ``linearize`` --- перераспределение элементов

.. code:: cpp

    boost::circular_buffer cb{3};

    cb.push_back(0);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);

    std::cout << std::boolalpha << cb.is_linearized() << '\n';

    auto ar1 = cb.array_one();
    auto ar2 = cb.array_two();
    std::cout << ar1.second << ";" << ar2.second << std::endl;

Куча
----

* `boost/heap/ <https://www.boost.org/libs/heap>`_
* Структура данных с частичным или полным упорядочиванием
* Расширение ``std::priority_queue``
* ``priority_queue`` позволяет не только вставлять элементы, но и итерироваться по ним
* ``binomial_heap`` позволяет:
  * итерироваться в упорядоченном массиве
  * производить слияние массивов
  * обновлять элементы
* ``fibonacci_heap`` предоставляет вставку за O(1)

.. code:: cpp

    boost::binomial_heap<int> bh;
    bh.push(2);
    bh.push(3);
    bh.push(1);

    boost::binomial_heap<int> bh2;
    bh2.push(4);
    bh.merge(bh2);

    std::copy(bh.ordered_begin(), bh.ordered_end(), std::ostream_iterator<int>(std::cout, "\n"));

Intrusive
---------

* `boost/intrusive/ <http://www.boost.org/libs/intrusive>`_
* Эффективное представление объектов через ``list`` и ``set`` с точки зрения попадания в кеш
  * Объекты хранятся отдельно от контейнера
  * Необходимо, чтобы их представление контейнера также попадало в кеш
  * Интеграция контейнерных данных внутрь объекта
* В качестве объектов подходят
  * наследники ``list/set_base_hook``
  * содержащие в себе переменную ``list/set_member_hook``
* Автоматическое удаление объекта из контейнера с помощью ``link_mode``

.. code:: cpp

    using namespace boost::intrusive;
    typedef link_mode<auto_unlink> mode;

    struct animal : public list_base_hook<link_mode<auto_unlink>>
    {
      std::string name;
      int legs;
    };

    animal a1{"cat", 4};
    animal a2{"ostrich", 2};
    animal *a3 = new animal{"spider", 8};

    list<animal, constant_time_size<false>> animals;

    animals.push_back(a1);
    animals.push_back(a2);
    animals.push_back(*a3);

    delete a3;

    for (const animal &a : animals)
        std::cout << a.name << '\n';

Массивы произвольной размерности
--------------------------------

* `boost/multi_array.hpp <https://www.boost.org/libs/multi_array>`_
* Количество размерностей --- константа, размеры размерностей задаются на уровне исполнения
* Используется ``boost::extents[N][M]`` для задания размера матрицы NxM
* Для получения среза массива достаточно вызвать ``operator[]``, либо использовать ``boost::indices``
* Метод ``origin`` предоставляет доступ к сырому указателю
* ``boost::multi_array_ref`` и ``boost::const_multi_array_ref`` являются обёртками над C-массивом

.. code:: cpp

    boost::multi_array<double, 3> a{boost::extents[3][6][8]};
    a[0][0][0] = 3.14;
    a[{0, 1, 1}] = 2.718;
    using range = boost::multi_array_types::index_range;
    auto view = a[boost::indices[range()][range() < 5][4 <= range().stride(2) <= 7]];
    std::transform(view.begin(), view.end(), [](auto x) { return x * 2; });

Контейнеры
----------

* `boost/container/ <https://www.boost.org/libs/container>`_
* Поддерживаются рекурсивные типы
* ``stable_vector`` позволяет изменять данные, при это итераторы всегда остаются валидными
* ``flat_set/map`` представляют "плоские" структуры, без деревьев
* ``slist`` == ``std::forward_list``
* ``static_vector`` подобен ``std::array``, но ведёт себя как ``std::vector``
* ``small_vector`` имеет преалоцированную память, подходит для массивов с малой длиной
