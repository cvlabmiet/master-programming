Структуры данных
================

Вошедшие в STL
--------------

* `boost/optional.hpp <https://www.boost.org/libs/optional>`_
* `boost/tuple.hpp <https://www.boost.org/libs/tuple>`_
* `boost/any.hpp <https://www.boost.org/libs/any>`_
* `boost/variant.hpp <https://www.boost.org/libs/variant>`_
* Также предоставляется заголовочный файл ``io`` для каждого из типов

Дерево свойств
--------------

* `boost/property_tree/ <https://www.boost.org/libs/property_tree>`_
* Предоставляет структуру для хранения ключ-значение
* Ключ может быть задан в виде пути
* Рекурсивный тип
* ``path_type`` позволяет использовать свой разделить в пути
* Писатели
  * ``put`` --- положить значение по ключу
  * ``put_child`` --- положить ``ptree`` по ключу
  * ``add_child`` --- добавить ``ptree`` к ключу (эмуляция массива)
* Читатели
  * ``get_value`` --- получить значение, тип определяется шаблонным параметром
  * ``get_optional`` --- получить значение или нет
  * ``get_child`` --- получить потомка ``ptree``
  * ``get_child_optional`` --- получить потомка или нет
* ``json_parser::write_json`` и ``json_parser::read_json`` дают возможность сериализовать ``ptree``
  * Также поддерживается ``ini_parser`` и ``xml_parser``

.. code:: cpp

    using boost::property_tree::ptree;

    ptree pt;
    pt.put("drive.win.system", "20 files");

    boost::optional<std::string> c = pt.get_optional<std::string>("drive");
    std::cout << std::boolalpha << c.is_initialized() << '\n';

    pt.put_child("drv.files", ptree{"50 files"});
    pt.add_child("drv.files", ptree{"60 files"});

    ptree d = pt.get_child("drv");
    for (const auto& [key, val] : d)
        std::cout << val.get_value<std::string>() << '\n';

    boost::optional<ptree&> e = pt.get_child_optional("ala");
    std::cout << e.is_initialized() << std::endl;

Динамический bitset
-------------------

* `boost/dynamic_bitset.hpp <https://www.boost.org/libs/dynamic_bitset>`_
* Динамическое решение для ``std::bitset``
* Оперирует блоками --- минимальный размер порций входных битов
* В процессе добавления битов меняет свой внутренний размер
* Повторяет интерфейс ``std::bitset``
* Может быть выведен в поток ввода/вывода
* Есть конструктор от итераторов + функция ``to_block_range`` позволяет сделать сериализацию данных

.. code:: cpp

    boost::dynamic_bitset<uint32_t> db{"11010110101"};

    db.push_back(true);
    db.append(4485);

    std::vector<uint32_t> v{{8, 779, 65564, 5321, 556}};
    db.append(v.begin(), v.end());

    std::cout.setf(std::ios::boolalpha);
    std::cout << db.size() << '\n';
    std::cout << db.count() << '\n';
    std::cout << db.any() << '\n';
    std::cout << db.none() << '\n';

    std::cout << db[0].flip() << '\n';
    std::cout << ~db[3] << '\n';

    std::cout << db << std::endl;

Трёхзначный булевый тип
-----------------------

* `boost/logic/tribool.hpp <https://boost.org/libs/logic>`_
* Промежуточное значение ``indeterminate``
* ``tribool_io.hpp`` для вывода всех состояний

.. code:: cpp

    using namespace boost::logic;

    std::cout.setf(std::ios::boolalpha);

    tribool b1 = true;
    std::cout << (b1 || indeterminate) << '\n';
    std::cout << (b1 && indeterminate) << '\n';

    tribool b2 = false;
    std::cout << (b2 || indeterminate) << '\n';
    std::cout << (b2 && indeterminate) << '\n';

    tribool b3 = indeterminate;
    std::cout << (b3 || b3) << '\n';
    std::cout << (b3 && b3) << '\n';

Сжатые пары
-----------

* `boost/compressed_pair.hpp <https://www.boost.org/libs/utility/compressed_pair.htm>`_
* Аналогичен ``std::pair``
* Если параметр шаблона пустой класс, тогда ``compressed_pair`` использует меньше памяти
* Доступ к значениям осуществляется через методы ``first()`` и ``second()``

.. code:: cpp

    struct empty {};

    std::pair<int, empty> p;
    boost::compressed_pair<int, empty> cp;
    std::cout << sizeof(p) << " vs. " << sizeof(cp) << std::endl;
