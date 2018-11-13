Алгоритмы
=========

Обобщённые алгоритмы
--------------------

* `boost/algorithm/ <https://www.boost.org/libs/algorithm>`_
* Иерархия директорий: ``cxx11``, ``cxx14``
* Повторяет и дополняет алгоритмы из стандарта
* Без предиката: ``one_of_equal``, ``all_of_equal``, ``any_of_equal``, ``none_of_equal``
* Расширенный ``copy``: ``copy_while``, ``copy_until``
* Расширенные предикаты: ``is_sorted``, ``is_increasing``, ``is_decreasing``
* Другие алгоритмы: ``clamp``, ``find_not``, ``find_backward``, ``gather``, ``hex``, ``is_palindrome``, ``is_partitioned_until``, ``apply_permutation``
* Алгоритмы адаптированы для работы над диапазонами
* Различные алгоритмы поиска: Boyer-Moore, Boyer-Moore-Horspool, Knuth-Morris-Pratt

.. code:: cpp

    using namespace boost::algorithm;

    std::cout << unhex("432b2b") << '\n';
    hex(vector<char>{'C', '+', '+'}, std::ostream_iterator<char>(std::cout, ""));

    vector v{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
    auto p = gather(v.begin(), v.end(), v.begin() + 4, [](auto x) { return x % 2 == 0; });
    std::cout << "position = [" << p.first << "," << p.second << "]\n";

Диапазоны
---------

* `boost/range/ <https://www.boost.org/libs/range>`_
* Обобщение над итераторами
* Поддерживаются все стандартные алгоритмы
* Всё, что имеет ``begin`` и ``end`` --- это диапазоны
* Адапторы позволяют трансформировать диапазоны на лету
  * ``filter`` --- фильтрация по предикату
  * ``key`` и ``values`` --- адапторы для ``map``
  * ``indirect`` нужен для разыменовывания указателей в массиве
  * ``tokenize`` --- разбиение строки на токены по регулярному выражению
* ``iterator_range`` --- на базе его можно организовать свои диапазоны
  * ``irange`` позволяет создавать целочисленный диапазон на лету
  * ``istream_range`` превращает стрим в диапазон

.. code:: cpp

    auto ir = boost::irange(0, 3);
    std::cout << boost::join(ir, ", ") << std::endl;

    auto sr = boost::istream_range<int>(std::cin);
    boost::copy(sr, std::ostream_iterator<int>{std::cout, "\n"});

Граф (BGL)
----------

* `boost/graph/ <https://www.boost.org/libs/graph>`_
* Три вида представления графа:
  * ``adjacency_list`` чаще всего используется
  * ``adjacency_matrix`` применяется, когда количество рёбер примерно соответствует квадрату количества вершин
  * ``edge_list`` представляется из себя адаптор
* ``adjacency_list<OutEdgeList, VertexList, Directed, VertexProperties, EdgeProperties, GraphProperties, EdgeList>``
  * Контейнеры для вершин и рёбер: ``vecS``, ``listS``, ``setS``, ...
  * Направленность графа: ``directedS``, ``undirectedS``
  * Различные свойства для вершин и рёбер, например, вес ``boost::property<boost::edge_weight_t, int>`` или ``boost::no_property``
* Функции для работы с графом:
  * ``add_vertex``, ``add_edge`` для добавления вершин и рёбер
  * ``out_edges``, ``in_edges``, ``adjacent_vertices`` для выяснения выходящих/входящих рёбер и соседних вершин

.. class:: column50

    .. figure:: https://www.boost.org/doc/libs/1_68_0/libs/graph/doc/figs/adj-matrix-graph2.gif

        Пример направленного графа

.. class:: column50

    .. figure:: https://www.boost.org/doc/libs/1_68_0/libs/graph/doc/figs/adj-list2.gif

        Пример хранения графа в ``adjacency_list``

.. code:: cpp

    enum vertex { A, B, C, D, E, F };
    std::vector<std::pair<vertex, vertex>> edges{{
        {B, C}, {B, F},
        {C, A}, {C, C},
        {D, E},
        {E, D},
        {F, A}
    }};

    std::array weights{{2, 1, 1, 1, 3, 4, 2}};
    boost::adjacency_list<boost::vecS, boost::vecS, boos::undirectedS> g{6, edges.begin(), edges.end(), weights.begin()};

    auto [first, last] = boost::edges(g);
    std::copy(first, last, std::ostream_iterator<typename decltype(g)::edge_descriptor>(std::cout, "\n"));

Алгоритмы на графах
-------------------

* Функции обхода графа:
  * ``breadth_first_search`` или обход в ширину (волновой обход)
  * ``depth_first_search`` или обход в глубину
  * ``uniform_cost_search`` обход по наиболее выгодным вершинам
* Для функций обхода существуют паттерны посетители, например, ``distance_map``, ``weight_map``, ``color_map``, ``predecessor_map``, ...
* Посетители принимают на вход выходной итератор
* Содержится около 13 алгоритмов на основе различных обходов графа

.. code:: cpp

    boost::array<int, 6> directions;
    boost::dijkstra_shortest_paths(g, B, boost::predecessor_map(directions.begin()));

    int p = A;
    while (p != B)
    {
        std::cout << p << '\n';
        p = directions[p];
    }
    std::cout << p << std::endl;
