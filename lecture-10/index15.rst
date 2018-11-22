Библиотеки для работы с приложением
===================================

Логирование
-----------

* `boost/log/ <https://www.boost.org/libs/log>`_
* Бэкенд --- поток ввода/вывода, в который будут выводится сообщения
* Фротнэнд --- объекты, через которые проходят сообщения в бэкенд, например, ``boost::log::sinks::asynchronous_sink``
  * По сути это фильтры
* Ядро --- синглтон ``boost::log::core::get()``, в котором регистрируются фронтэнды
  * Если фильтры зарегистрированы в самом ядре, это глобальные фильтры
  * Если фильтры зарегистрированы во фронтэнде, это локальные фильтры фронтэнда
* Логер --- через него записываются сообщения пользователем
  * Макрос ``BOOST_LOG`` позволяет использовать интерфейс ``std::ostream``
  * Макрос ``BOOST_LOG_SEV`` позволяет дополнительно передавать уровень логирования
* Собственный фильтр --- функция, аргумент которой ``attribute_value_set``, возвращает тип ``bool``
* Собственный форматер --- функция с сигнатурой ``void(const record_view& view, formatting_ostream& os)``
  * Из ``view`` можно получить ``attribute_value_set`` через функцию ``attribute_values()``
  * Вывод необходимо направлять в ``os``
* ``BOOST_LOG_ATTRIBUTE_KEYWORD`` позволяет создавать атрибуты
  * Задавать их можно сразу во фронтэнде с помощью ``boost::log::expressions`` (отсылка к Xpressive)
  * Форматер также может быть написан в виде лямбда-выражения
* Макрос ``BOOST_LOG_SCOPED_LOGGER_ATTR`` позволяет задавать локальный атрибут
* Исключения обрабатываются в ядре, путём установки посетителя через метод ``set_exception_handler``

.. code:: cpp

    using namespace boost::log;

    BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", int)
    BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(lg, sources::severity_logger<int>)

    int main()
    {
        auto sink = std::make_shared<sinks::asynchronous_sink<sinks::text_ostream_backend>>();
        std::shared_ptr stream{&std::clog, boost::empty_deleter{}};

        sink->locked_backend()->add_stream(stream);
        sink->set_filter(severity > 0);
        sink->set_formatter(expressions::stream << severity << ": " << expressions::smessage);

        core::get()->add_sink(sink);

        BOOST_LOG_SEV(lg::get(), 0) << "note";
        BOOST_LOG_SEV(lg::get(), 1) << "warning";
        BOOST_LOG_SEV(lg::get(), 2) << "error";
        sink->flush();
    }

Аргументы командной строки
--------------------------

* `boost/program_options.hpp <https://www.boost.org/libs/program_options>`_
* 
