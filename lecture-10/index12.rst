Языковые расширения
===================

Coroutine
---------

* `boost/coroutine2/ <https://www.boost.org/libs/coroutine2>`_
* Переключение исполнения функции по точкам синхронизации
* В некоторых языках это ключевые слова ``yield`` и ``await``
* Построение coroutine с помощью типов ``pull_type`` и ``push_type``
* Для обеспечения передачи аргументов используется ``tuple``


.. code:: cpp

    using boost::coroutines2::coroutine;

    auto cooperative = [](coroutine<std::tuple<int, std::string>>::pull_type &source) {
        auto args = source.get();
        std::cout << "first = " << std::get<0>(args) << " " << std::get<1>(args) << "\n";
        source();
        args = source.get();
        std::cout << "second = " << std::get<0>(args) << " " << std::get<1>(args) << "\n";
    };

    coroutine<std::tuple<int, std::string>>::push_type sink{cooperative};
    std::cout << "start: "
    sink(std::make_tuple(0, "aaa"));
    std::cout << "next: ";
    sink(std::make_tuple(1, "bbb"));
    std::cout << "end\n";

Будет выведено::

    start: first = 0 aaa
    next: second = 1 bbb
    end

Parameter
---------

* `boost/parameter.hpp <https://www.boost.org/libs/parameter>`_
* Предоставляет ассоциативные параметры функций, как в языке python
* Заменяет так называемую Named Parameter Idiom
* Макросы ``BOOST_PARAMETER_FUNCTION`` и ``BOOST_PARAMETER_NAME`` делают всю работу
* Дополнительные макросы для работы с методами класса и шаблонами

.. code:: cpp

    BOOST_PARAMETER_NAME(a)
    BOOST_PARAMETER_NAME(b)
    BOOST_PARAMETER_NAME(c)
    BOOST_PARAMETER_NAME(d)
    BOOST_PARAMETER_NAME(e)

    BOOST_PARAMETER_FUNCTION(
        (void),
        complicated,
        tag,
        (required
            (a, (int))
            (b, (char)))
        (optional
            (c, (double), 3.14)
            (d, (std::string), "Boost")
            (e, *, true))
    )
    {
        std::cout.setf(std::ios::boolalpha);
        std::cout << a << '\n';
        std::cout << b << '\n';
        std::cout << c << '\n';
        std::cout << d << '\n';
        std::cout << e << '\n';
    }

    int main()
    {
        complicated(_b = 'B', _a = 1, _d = "lala");
    }

Conversion
----------

* `boost/cast.hpp <https://www.boost.org/libs/conversion/cast.htm>`_
* Расширение возможностей ``dynamic_cast``
* ``boost::polymorphic_downcast`` для кастования к наследнику из базового класса
* ``boost::polymorphic_cast`` для кастования между базовыми классами
* Всегда генерирует исключение при ошибке

.. code:: cpp

    struct base1 { virtual ~base1() = default; };
    struct base2 { virtual ~base2() = default; };
    struct derived : public base1, public base2 {};

    void downcast(base1 *b1)
    {
        derived *d = boost::polymorphic_downcast<derived*>(b1);
    }

    void crosscast(base1 *b1)
    {
        base2 *b2 = boost::polymorphic_cast<base2*>(b1);
    }

    int main()
    {
        derived *d = new derived;
        downcast(d);

        base1 *b1 = new derived;
        crosscast(b1);
    }
