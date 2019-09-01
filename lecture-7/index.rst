==================
Master programming
==================

---------------------------
Лекция №7 (Современный C++)
---------------------------

:Author: Игорь Шаронов
:Date: 2018-10-03

.. role:: cpp(code)
    :language: cpp

Обзор стандартов
================

Возможности языка на примере стандарта C++98
--------------------------------------------

* https://isocpp.org, https://cppreference.com
* STL (1994 г.)--- не является частью языка, но входит в стандарт
* Конструкторы и деструкторы
* Наследование и полиморфизм
* Шаблонные классы
* Шаблонные функции
* Специализации шаблонов и перегрузка функций
* Константность объектов, методов, выражений (:cpp:`constexpr`)
* Пространства имён
* Исключения
* Строже типизирован, чем язык C

Инкапсуляция, наследование, полиморфизм
---------------------------------------

* Инкапсуляция позволяет прятать сущности:
  * Агрегированные объекты
  * Наследование --- способ реализации интерфейсов
* Наследование --- компилятор по типу класса определяет таблицу функций
* Наследование в полиморфизме:
  * Справедливо только для указателей или ссылок на базовый класс
  * Работает в рантайме
  * Компилятор не может по типу указателя базового класса определить тип объекта
  * Каждый объект содержит указатель на таблицу функций (методов)
    * Таблицы функций используются одни и те же для одинаковых типов

Перегрузка
----------

* Перегрузка функций возможна только в сигнатуре
  * Возвращаемое значение не входим в сигнатуру (в C++)
* Специализация класса --- это тоже вид перегрузки
* Частичная специализация класса
  * Частичной специализации функций не бывает (не отличимо от обычной перегрузки)
* Можно делать только специализации
  * Более общий шаблонный класс останется пустым
  * Сигнализация об ошибке будет только в том случае, если не подойдёт ни одна специализация

SFINAE
------

* `Substitution Failure Is Not A Error <http://en.cppreference.com/w/cpp/language/sfinae>`_
* Если вывод специализации приводит к ошибке, то
  * данная специализация отбрасывается
  * переходим к следующей специализации

.. code:: cpp

    template <class T> int f(typename T::B*);
    template <class T> int f(T);
    int i = f<int>(0); // uses second overload

Шаблоны
-------

* Уровень компиляции
* :cpp:`template<class T> int func()`, где ``T`` --- шаблонный параметр
* :cpp:`func<int>()`, где :cpp:`int` --- аргумент шаблона
* Параметр шаблона может быть не-типовым (int, char, short, ...)
  * :cpp:`template<size_t N> int get()`
  * Исключения: это не указатель и не тип :cpp:`double` или :cpp:`float`
* Специализация функции --- :cpp:`template<> int func<float>()`

Обзор стандарта C++03
=====================

Нововведения
------------

* Развивается библиотека Boost
* Technical Report
* Больше особо нечем гордиться

Обзор стандарта C++11
=====================

Новые возможности языка
-----------------------

* Ключевое слово :cpp:`auto`
  * :cpp:`int k;` == :cpp:`decltype(k) v;`
* Возвращаемое значение может быть написано после имени функции :cpp:`auto func(char x) -> int;`
* Появление неименнованных функций (лямбда-выражения)
  * :cpp:`auto f = [](int x) -> double { return std::pow(x, 1.35); };`
  * :cpp:`[a, &b, =, &]` --- замыкание области видимости: по значению, по ссылке, замыкания всей области видимости
* :cpp:`constexpr` --- функция выполнения на уровне компиляции :cpp:`int n[func(79)]`
* Универсальная инициализация через ``{}``
  * :cpp:`myclass s(7, 9, 8)` и :cpp:`myclass s{7, 9, 8}` --- одно и то же
  * теперь структуры без конструктора и с конструктором могут быть проинициализированы одинаково
* xvalue, rvalue, prvalue --- move-нотации
* Цикл по коллекции :cpp:`for (const auto& x : array) { ... }`

Новые возможности языка (продолжение)
-------------------------------------

* :cpp:`override`, :cpp:`final` --- помогает отлавливать неправильные переопределения в полиморфизме
* :cpp:`noexcept` --- постепенный отказ от перечисления исключений в сигнатуре
* :cpp:`nullptr` вместо :cpp:`NULL` и введение :cpp:`nullptr_t`
* :cpp:`enum class` (всё ещё нет автоматического преобразования в строку)
* :cpp:`static_assert` --- ассерт на уровне компиляции
* :cpp:`alignas(T)` --- выравнивание данных как у ``T``
* **Вариативные шаблоны**

Расширение STL
--------------

* ``std::tuple``, ``std::array``, ``std::unordered_map/set``, ``std::chrono``
* ``std::thread``, ``std::mutex``, ``std::conditional_variable``, ``std::atomic`` и ``thread_local``
* Методы ``emplace``
* ``std::shared_ptr``, ``std::weak_ptr``, ``std::unique_ptr``
* ``std::function``
* ``std::future``, ``std::promise``
* ``std::hash``
* ``std::type_index``
* ...

Обзор стандарта C++14
=====================

Новые возможности языка
-----------------------

* Автоматический вывод возвращаемого значения :cpp:`auto func();`
* :cpp:`decltype(auto)` --- там, где :cpp:`auto` отбрасывает слишком много
* Шаблонные переменные :cpp:`template<class T> T xxx = T(2.78962161L);`
* Агрегатная инициализация

    .. code:: cpp

        struct abc
        {
            int x = 47;
            bool f = true;
            std::string s = "abc";
        };

* Литералы двоичных чисел и разделители разрядов :cpp:`0b10110`, :cpp:`100'500`
* Обобщённые лямбда-выражения :cpp:`[](auto x) { return x*x + 1; }`
* Атрибут :cpp:`[[deprecated]]`

Нововведения в STL
------------------

* Пользовательские литералы :cpp:`auto dur = 60s;`
* :cpp:`std::cbegin/std::cend`
* :cpp:`std::make_index_sequence` для :cpp:`std::integral_constant` полезен при разворачивании кортежа в аргументы

Обзор стандарта C++17
=====================

Новые возможности языка
-----------------------

* Упакованные выражения :cpp:`template<class... Ts> bool foo(Ts... args) { return (args && ...); }`
* Инициализация переменной в :cpp:`if` и :cpp:`switch`: :cpp:`if (auto a = getA(); a.isValid()) ...`
* Автоматический вывод аргументов шаблона класса :cpp:`std::vector v{{7, 8, 9}}`
* Structured binding declarations :cpp:`const auto& [x, y] = mystruct_object;`
* :cpp:`[[fallthrough]]`, :cpp:`[[nodiscard]]`, :cpp:`[[maybe_unused]]`
* Вложенные пространства имён :cpp:`namespace A::B {}` == :cpp:`namespace A { namespace B {} }`
* :cpp:`if constexpr` взамен :cpp:`std::enable_if` и SFINAE

Нововведения в STL
------------------

* :cpp:`std::optional`, :cpp:`std::variant`, :cpp:`std::any`
* Поддержка параллельных алгоритмов
* Символьные литералы для UTF-8 :cpp:`u8`, :cpp:`u`, :cpp:`U`
* :cpp:`std::filesystem`
* :cpp:`std::string_view`
* ``hardware_constructive_interference_size`` и ``hardware_destructive_interference_size`` --- влияние аппаратного кеша
* :cpp:`std::byte`

Обзор современных особенностей языка C++
========================================

О using директиве
-----------------

* Алиас типа: :cpp:`using type_int = int;`
* Шаблонные алиас типа: :cpp:`template<class T> using my_vector = std::vector<T>;`
* Расширение области видимости:
  * пространства имён :cpp:`using namespace std;`
  * методов базового класса :cpp:`using Base::method1;`
    * попадают все сигнатуры ``method1``
  * конструкторов :cpp:`using Base::Base`
    * если класс шаблонный, необходимо указать имя самого класса :cpp:`using Derived::Base::Base;`
    * наследуются все конструкторы из ``Base``, кроме автогенерируемых конструкторов ``Base``
* Проблема пересечения имён

О rvalue
--------

* Copy elision

  .. code:: cpp

      T f() { return T(); }
      T x = f(); // конструктор копирования не будет вызван

* Типы ссылок

  .. class:: column66

      * lvalue --- обычная ссылка ``&`` или то, что **имеет имя**
      * rvalue --- ``&&``, используется чтобы "переместить" содержимое объекта
      * prvalue --- результат выражения или то, что **не имеет имени** (42, например)
      * xvalue --- временный объект, который имеет имя, но являет rvalue
      * glvalue --- обобщение xvalue и lvalue

  .. class:: column33

        .. image:: ref.dot.svg

* Perfect forwarding и `универсальная ссылка <https://habr.com/post/242639>`_

  .. code:: cpp

    template<class... Args> void func(Args&&... args) {
        some_func(std::forward<Args>(args)...);
    }

    std::vector v = {7, 8, 56, 98, 5, 0, -1, 8};
    func(v); // [Args = {std::vector<int>&}], & && == &
    func(std::move(v)); // [Args = {std::vector<int>&&}], && && == &&
    func(std::vector{7.0, 8.3, -96.87, 7.1}); // [Args = {std::vector<double>}], () == &&

О конструкторах
---------------

.. code:: cpp

    class A {
    public:
        A(); // default constructor
        A(const A&); // copy constructor
        A(A&&); // move constructor
        A& operator=(const A&); // copy assignment
        A& operator=(A&&); // move assignment
        ~A(); // destructor
    }

* Порождающие операторы: конструкторы, присваивания, деструктор
* Деструктор почти всегда генерируется сам, его перегрузка ни на что не влияет
* Перегрузка move-конструктора или move-присваивания затрагивает все операции
* Перегрузка конструктора копирования или присваивания не затрагивает move-операции
* :cpp:`delete` --- явное удаление порождающего оператора
* :cpp:`default` --- попросить компилятор сгенерировать порождающий оператор
* Явное правило вывода конструктора: :cpp:`template<class T> myclass(T&&, int) -> myclass<T>;`

О шаблонах
----------

* :cpp:`template<class... Ts> class myclass;` --- пакет шаблонных параметров
* :cpp:`template<class T> constexpr T pi = T(3.1415926535897932385L);` --- шаблонная переменная
* :cpp:`size_t N = sizeof...(Ts);`
* Хранение аргументов в кортеже

  .. code:: cpp

        template<class... Ts>
        struct abc {
            abc(Ts... ts): x(ts...) {}

            std::tuple<Ts...> x;
        }

Распаковка кортежа в аргументы
------------------------------

* Использование :cpp:`std::integer_sequence`

  .. code:: cpp

    template<class... Ts>
    void func1(const std::tuple<Ts...>& t)
    {
        func_impl(t, std::make_sequence_for<Ts...>{});
    }

    template<class Tuple>
    void func2(const Tuple& t)
    {
        func_impl(t, std::make_index_sequence<std::tuple_size_v<Tuple>>{});
    }

    template<class Tuple, size_t... Is>
    void func_impl(const Tuple& t, std::index_sequence<Is...>)
    {
        (std::cout << ... << std::get<Is>(t));
    }

    template<class... Ts>
    std::ostream& operator<<(std::ostream& os, const std::tuple<Ts...>& t)
    {
        return std::apply([&os](const auto&... xs) -> decltype(auto) { return (os << ... << xs); }, t);
    }

Операции над шаблонными пакетами
--------------------------------

.. code:: cpp

    template <typename... bases>
    struct X : bases... {
        using X::bases::g...;
    };
    X<B, D> x;

Свёртки (наличие скобок важно)

* :cpp:`( pack op ... )` --- свёртка слева
* :cpp:`( pack op ... op init )` --- свёртка слева с начальным значением
* :cpp:`( ... op pack )` --- свёртка справа
* :cpp:`( init op ... op pack )` --- свёртка справа с начальным значением

.. code:: cpp

    template<typename T, typename... Args>
    void push_back_vec(std::vector<T>& v, Args&&... args)
    {
        (v.push_back(std::forward<Args>(args)), ...);
    }

О лямбда-выражениях
-------------------

:cpp:`auto f = [a = 77, &b](auto x) mutable -> int { b = x - 78; return a++; }`

* Лямбда-выражения == функторы

  .. code:: cpp

    struct functor
    {
        functor(int& b): a_(77), b_(b) {}
        int operator()(int x) const
        {
            b_ = x - 78;
            return a_++;
        }

    private:
        mutable int a_;
        int& const b_;
    } f;

* Невозможно узнать тип лямбда-выражений, т.е. :cpp:`decltype(lambda) s = ...` не работает
* Чтобы лямбды были полностью объектами, надо заворачивать их в объект :cpp:`std::function`
* Результат лямбды можно не писать, он будет выведен сам (кроме ссылок)

Следующие стандарты
===================

Концепты и ограничители
-----------------------

.. code:: cpp

    // концепт
    template<typename T>
    concept EqualityComparable = requires(T a, T b)
    {
        { a == b } -> bool;
    };

    // ограничитель: T должен обладать оператором ==
    template<EqualityComparable T> void f(T&&);

    // или
    template<class T> requires EqualityComparable<T> void f(T&&);

* Компактнее вывод об ошибке (с концептами --- 2 строки, без них --- 50+)
* По сигнатуре можно понять, какой тип данных ожидает функция
* Ещё один способ ужесточения типизации

Новое в STL
-----------

* :cpp:`std::bit_cast` --- замена :cpp:`reinterpret_cast`
* Стандартные концепты (Integral, Assignable, Constructible, ...)
* Шаблонный тип может быть классом :cpp:`template<X x> void func()` (есть ограничения, например, :cpp:`operator<=>`)
* :cpp:`operator<=>` --- один оператор покрывает все отношения порядка и равенства (spaceship)
* Все новые особенности языка можно проверить с помощью препроцессорных констант
  * например, :cpp:`__cpp_lib_byte` говорит о наличии :cpp:`std::byte`
* :cpp:`std::span` --- декоратор над непрерывной областью памяти
* Ranges --- поддержка концепции диапазонов из ``boost::range``
* :cpp:`std::is_detected` --- детектирование наличия метода/оператора класса
