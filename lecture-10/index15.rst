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
* Опции командной строки
  * Позиционные (``git remote prune origin``)
  * Непозиционные
    * С аргументом, который отделяется пробелом или ``=``
    * С аргументами (зависит от самой команды)
    * Без аргументов
    * Длинные команды с двойным дефисом ``--``, команда пишется полностью, в BSD используется один дефис
    * Короткие с одинарным дефисом, от команды остаётся одна буква (обычно первая), пробел перед аргументом можно не писать
    * Команды со слешем
* Представляет опции командной строки в виде ассоциативного массива
* Поддерживаются значения по умолчанию для аргументов
  * ``--has-default positional options here`` => ``--has-default -- positional options here``
* Возможность считывать флаги из файла
* Некоторая громоздкость при создании ``variables_map``, стоит взглянуть на `cxxopts <https://github.com/jarro2783/cxxopts>`_
* В случае провала генерируется исключение ``boost::program_options::error``
* С помощью ``parse_environment()`` и ``environment_iterator`` можно загружать опции через переменные окружения

.. code:: cpp

    using namespace boost::program_options;

    options_description generalOptions{"General"};
    generalOptions.add_options()
        ("help,h", "Help screen")
        ("config", value<std::string>()->default_value("/etc/config.cfg"), "Config file")
        ("age", value<int>(), "Age");

    variables_map vm;
    store(parse_command_line(argc, argv, generalOptions), vm);
    if (vm.count("config"))
    {
        std::ifstream ifs{vm["config"].as<std::string>()};
        if (ifs)
            store(parse_config_file(ifs, fileOptions), vm);
    }
    notify(vm);

    if (vm.count("help"))
        std::cout << generalOptions << std::endl;
    else if (vm.count("age"))
        std::cout << "Your age is: " << vm["age"].as<int>() << std::endl;

Примерный вывод::

    [09:31] igor@nixos-pc tmp [nix-shell] % ./out -h
    General:
        -h [ --help ]                   Help screen
        --config arg (=/etc/config.cfg) Config file
        --age arg                       Age

    [09:33] igor@nixos-pc tmp [nix-shell] % ./out --age 21
    Your age is: 21
    [09:39] igor@nixos-pc tmp [nix-shell] % cat ./abc.cfg
    age = 22
    [09:39] igor@nixos-pc tmp [nix-shell] % ./out --config ./abc.cfg
    Your age is: 22

Сериализация
------------

* `boost/ <https://www.boost.org/libs/serialization>`_
* Процесс представления объектов в бинарном виде, который можно сохранить в поток либо восстановить в объект
* В большинстве случаев формат сериализации избыточен
* ``boost::archive::text_oarchive`` и ``boost::archive::text_iarchive`` --- простейшие сериализаторы, обёртки над стримами
* Чтобы сериализовать свой класс, необходимо
  * Зафрендить класс ``boost::serialization::access``
  * Реализовать метод ``void serialize(Archive& ar, const unsigned int version)``
    * Шаблонный параметр ``Archive`` --- это сериализатор
    * Считывать/записывать значения в ``ar`` нужно с помощью оператора ``&``
    * Версия привязана к сериализации объекта
  * Сериализовать следует требуемые переменные класса
  * Сериализация происходит рекурсивно
  * Можно реализовать отдельную функцию ``void serialize(Archive& ar, MyAwesomeObject& a, const unsigned int version)``
* Объявление версии объекта делается через макрос ``BOOST_CLASS_VERSION(MyAwesomeObject, 42)``
* Умеет работать с умными указателями и создавать объекты в куче
* Сериализация базового класса в наследнике делается через приведение к ``boost::serialization::base_object<BaseClass>(*this);``
  * Чтобы сериализовать потомок через указатель базового класса, необходимо задекларировать его через ``BOOST_CLASS_EXPORT``
* Оптимизаторы для сокращения битового потока сериализованного объекта
  * Массивы могут быть оптимизированы с помощью вызова ``boost::serialization::make_array(a.data(), a.size())``
  * ``make_binary_object`` используется для сырых данных, например, бинарные данные изображения

.. code:: cpp

    using namespace boost::archive;

    class animal
    {
    public:
        animal(int legs = 0) : legs_{legs} {}
        int legs() const { return legs_; }

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive &ar, const unsigned int version) { ar & legs_; }

        int legs_;
    };

    class bird : public animal
    {
    public:
        bird(bool can_fly = true) : animal{2}, can_fly_{can_fly} {}
        bool can_fly() const { return can_fly_; }

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            ar & boost::serialization::base_object<animal>(*this);
            ar & can_fly_;
        }

        bool can_fly_;
    };

    std::stringstream ss;

    auto serialize = [](auto& os, const bird& obj) {
        text_oarchive oa{os};
        oa << obj;
    };

    auto deserialize = [](auto& is) {
        text_iarchive ia{is};
        bird obj;
        ia >> obj;
        return obj;
    };

    bird penguin{false};
    serialize(ss, penguin);

    bird b = deserialize(ss);
    std::cout << b.legs() << " " << std::boolalpha << b.can_fly() << std::endl;

UUID
----

* `boost/uuid/ <https://www.boost.org/libs/uuid>`_
* Universal Unique Identifier в большинстве случаем случайная последовательность чисел стандартизованного формата
* POD тип размера 128 битов
* Не может быть создан напрямую, только через генератор
  * ``nil_generator`` производит нулевой UUID ``00000000-0000-0000-0000-000000000000``
  * ``random_generator`` полностью случайный UUID
  * ``string_generator`` для генерации UUID из строки по стандарту
  * ``name_gen`` для получения UUID строки
* Доступные методы
  * ``size`` размер, всегда равен 16 байтам
  * ``is_nil`` является ли UUID нулевым
  * ``variant`` и ``version`` позволяют понять, какой стандарт использовался при генерации UUID
* Метод ``to_string`` или ``boost::lexical_cast<std::string>`` позволяет получить UUID в виде строки

.. code:: cpp

    boost::uuids::string_generator string_gen;
    boost::uuids::uuid id = string_gen("CF77C981-F61B-7817-10FF-D916FCC3EAA4");
    std::cout << id.variant() << ":" << id.version() << " = " << id << std::endl;
