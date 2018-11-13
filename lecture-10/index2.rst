Обработка строк
===============

Строковые алгоритмы
-------------------

* `boost/algorithm/string.hpp <https://www.boost.org/libs/algorithm/string>`_
* Алгоритмы поиска ``find_*`` [1]
* Алгоритмы удаления ``erase_*_copy``
* Алгоритмы замены ``replace_*_copy``
* Алгоритмы отсечения ``trim_left/right/_copy``, может использовать предикаты
* Предикаты ``is_any_of``, ``is_digit``, ``is_upper``, ``is_lower``, ``is_space``, ...
* Алгоритмы сравнения ``starts_with``, ``ends_with``, ``contains``, ``lexicographical_compare``
* Поиск по регулярному выражению ``find_regex``
* Конкатенация ``join``

  .. code:: cpp

    std::vector v{{7, 8, 59}};
    std::cout << boost::join(v, ",") << std::endl;

* Разделение строки ``split``

  .. code:: cpp

    std::string s = "Boost C++ Libraries";
    std::vector<std::string> v;
    boost::split(v, s, boost::is_space());
    std::cout << v.size() << std::endl;

[1] Символ ``*`` --- это ``first``, ``nth``, ``last``, ``all``, ``head``, ``tail``

Лексические преобразования
--------------------------

* `boost/lexical_cast.hpp <https://www.boost.org/libs/lexical_cast>`_
* Обобщённая замена ``std::itoa`` в обе стороны
* Работает только с теми типами, для которых перегружены операторы ввода/вывода ``>>`` и ``<<``
* В случае ошибки кидает исключение ``bad_lexical_cast``

.. code:: cpp

    std::string s = boost::lexical_cast<std::string>(123);
    double d = boost::lexical_cast<double>(s);
    std::cout << s << " == " << d << std::endl;

Форматированный вывод
---------------------

* `boost/format.hpp <https://www.boost.org/libs/format>`_
* Обобщённая замена ``std::printf``
* Аргументы разделяются оператором ``%``
* В строке параметры выглядят как ``%1%``, ``%2%`` и т.д.
* Поддерживаются стандартные манипуляторы через ``boost::io::group``, которому также передаётся номер параметра, к которому манипулятор применяется
* Использование специальных символов, например, ``%|1$+|``
* В случае ошибок формата, программа кидает исключение
* Также поддерживается формат ``std::printf``

.. code:: cpp

    std::cout << boost::format{"0x%|1$#| %2%"} % 123 % 456 << std::endl;

Регулярные выражения
--------------------

* `boost/regex/ <https://www.boost.org/libs/regex>`_
* Почти полностью соответствует ``std::regex``
* ``regex_match`` --- одиночный матч
* ``regex_search`` --- поиск соответствия с группировкой
* ``regex_replace`` --- позволяет делать замены (для замен групп используются ``\\1``, ``\\2`` и т.д.)
* ``regex_token_iterator`` --- позволяет итерироваться по группам
* Можно подключать локаль в регулярных выражениях ``cpp_regex_traits`` и ``imbue``

.. code:: cpp

    std::string s = "Boost Libraries";
    boost::regex expr = R"((\w+)\s*(\w+))";
    if (boost::smatch what; boost::regex_search(s, what, expr))
    {
        std::cout << what[0] << '\n';
        std::cout << what[1] << "_" << what[2] << '\n';
    }

Xpressive
---------

* `boost/xpressive/ <https://www.boost.org/libs/xpressive>`_
* Написание регулярных выражений с помощью синтаксиса языка C++
* Регулярные выражения на уровне компиляции
* Есть аналогичный механизм записи регулярных выражений ``sregex::compile`` как в ``boost::regex``
* Синтаксис замены: ``\w`` → ``_w``, ``\s`` → ``_s`` и т.д.

  .. code:: cpp

    using namespace boost::xpressive;

    std::string_view s{"Boost Libraries"};
    auto r = sregex::compile(R"(\w+\s*\w+)");
    auto r2 = +_w >> _s >> +_w;
    std::cout << regex_match(s, r) << " == " << regex_match(s, r2) << std::endl;

* Можно присоединять к найденному выражению действия через оператор ``[]``

  .. code:: cpp

    using namespace boost::xpressive;

    std::string_view s{"Boost Libraries"};
    std::ostream_iterator<std::string> it{std::cout, "\n"};
    auto r = (+_w)[*ref(it) = _] >> _s >> +_w;
    std::cout << std::boolalpha << regex_match(s, r) << std::endl;

* ``_`` означает текущее найденное выражение
* Аналогичный подход используется в ``boost::spirit``
* Запись внутри ``[]`` является лямбда выражением, аналогичным в ``boost::lambda``

Токенайзер
----------

* `boost/tokenizer.hpp <https://www.boost.org/libs/tokenizer>`_
* Позволяет итерироваться по строке, содержащей сепаратор
* ``boost::char_separator`` основной класс сепаратора, конструктор принимает
  #. Символы-разделители
  #. Какие символы-разделители не должны подавляться в выводе
  #. Дополнительные флаги
* ``escaped_list_separator``: разделитель символ ``,``, все символы возврата обрабатываются
  * Парсинг CSV
* ``offset_separator`` задаёт конкретные интервалы сепаратора. Подходит для бинарного анализа файла

.. code:: cpp

    std::string_view s{"Boost C++ Libraries"};
    boost::char_separator<char> sep{" ", "+", boost::keep_empty_tokens};
    boost::tokenizer tok{s, sep};
    for (const auto &t : tok)
        std::cout << t << '\n';

Spirit
------

* `boost/spirit/ <https://www.boost.org/libs/spirit>`_
* Замена EBNF и PEG на уровне компиляции
* Состоит из (версия 2.x)
  * Qi --- разработка парсеров (устарел в пользу ``x3``)
  * Karma --- разработка генераторов
  * Lexers --- разработка анализаторов лексем (устарел)
* Основные точки входа:
  * ``qi::parse`` --- применяет парсер/грамматику для итератора
  * ``qi::phrase_parse`` --- повторяет предыдущее + умеет игнорировать пробельные символы
  * Обе функции останавливаются, когда парсер исчерпается. Первый итератор будет смещён на позицию остановки
* Остальное API
  * Примитивные парсеры
  * Действия (устарело)
  * Атрибуты
  * Правила
  * Грамматики (устарело)
* Подробнее см. в лекции, посвящённой ``boost::spirit::x3``
