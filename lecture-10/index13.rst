Обработка ошибок
================

System
------

* `boost/system/ <https://www.boost.org/libs/system>`_
* Содержит специальные классы с ошибками: ``error_code``, ``errc::make_error_code``, ...
* Переехал полностью в C++11
* Поддерживает posix-совместимые ошибки
  * Есть информация о номере ошибки
  * Человеческое имя ошибки
  * К какой категории относится
* Путём наследования от ``boost::system::error_category``
* ``error_code`` для платформо специфичных ошибок, ``error_condition`` для всех платформ
* ``boost::system::system_error`` используется для генерации исключения на базе ``error_code``

.. code:: cpp

    try
    {
        throw system_error{errc::make_error_code(errc::not_supported)};
    }
    catch (system_error& e)
    {
        error_code ec = e.code();
        std::cerr << ec.value() << '\n';
        std::cerr << ec.category().name() << std::endl;
    }

Исключения
----------

* `boost/exception/ <https://www.boost.org/libs/exception>`_
* Дополняет функциональность ``std::exception``
* Макрос ``BOOST_THROW_EXCEPTION`` позволяет сохранять информацию о файле и строчке исключения
* В исключение можно дописать дополнительную информацию с помощью ``boost::error_info``
  * В STL этот механизм называется ``std::nested_exception``
* ``boost::diagnostic_information`` для получения всей информации об исключении
* ``boost::get_error_info`` вывод информации об исключении напрямую

.. code:: cpp

    error_info = boost::error_info<struct tag_errmsg, std::string> errmsg_info;

    try
    {
        try
        {
            BOOST_THROW_EXCEPTION(std::runtime_error{"123"});
        }
        catch (boost::exception &e)
        {
            e << errmsg_info{"writing lots of zeros failed"};
            throw;
        }
    }
    catch (boost::exception &e)
    {
        std::cerr << *boost::get_error_info<errmsg_info>(e);
        std::cerr << boost::diagnostic_information(e);
    }
