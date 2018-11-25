Дизайн паттерны
===============

Легковес
--------

* `boost/flyweight.hpp <https://www.boost.org/libs/flyweight>`_
* Применяется там, где нужно сохранять повторяющиеся значения в полях объекта
* Использует контейнеры с уникальным ключом для хранения объектов
* Разделение по типам, либо можно задать свой тэг
* Дополнительные шаблонные параметры в типе легковеса
  * ``set_factory`` использовать ``std::set`` для хранения объектов, а не хешированный массив
  * ``no_locking`` не использовать примитивы синхронизации а-ля мьютексы
  * ``no_tracking`` не отслеживать время жизни объект
    * По умолчанию объект умирает, когда все ссылки на него прекращаются

.. code:: cpp

    struct person
    {
        struct country {};

        int id;
        flyweight<std::string> city;
        flyweight<std::string, tag<country>> country;
        person(int _id, std::string _city, std::string _country)
            : id{_id}, city{std::move(_city)}, country{std::move(_country)} {}
    };

    std::vector<person> persons;
    for (int i = 0; i < 100000; ++i)
        persons.push_back({i, "Berlin", "Germany"});

Signals2
--------

* `boost/signals2.hpp <https://www.boost.org/libs/signals2>`_
* Концепция сигналов и слотов или событийный паттерн
* Сигналы чем-то напоминают ``std::function``
* ``connect`` позволяет подсоединять свои функции к определённому сигналу (слоты)
  * ``disconnect`` обратное действие
  * ``num_slots`` позволяет узнать, сколько обработчиков подписано на этот сигнал
  * Сигнатура обработчика записывается в сигнатуре сигнала
* Можно получить возвращаемое значение последнего обработчика через ``operator*``
  * Есть возможность задать компоновщика возвращаемых значений, он принимает InputIterator
* ``boost::signals2::shared_connection_block`` используется для временного прекращения работы слота

.. code:: cpp

    boost::signals2::signal<void()> s;

    auto hello = [] {
        std::cout << "Hello, world!" << std::endl;
    };

    auto disconnect = [&s, hello] {
        s.disconnect(hello);
    };

    s.connect(hello);
    s.connect(disconnect);
    s();
    s();

Машина состояний
----------------

* `boost/msm/ <https://www.boost.org/libs/msm>`_
* Машина состояний строится из состояний, событий, атрибутов событий (действий), гардов
* FSM (Finite State Machine) задаётся с помощью таблицы переходов
  * Каждая строка таблицы содержит начальное состояние, событие, конечное состояние, атрибут, гард
  * ``row`` определяет полную строку таблицы
  * ``a_row`` определяет строку таблицы с атрибутом, но без гарда
  * ``g_row`` позволяет опускать определение атрибута
  * ``_row`` позволяет опускать определение атрибута и гарда
* Есть вспомогательные макросы для описания всех частей FSM
* MSM предлагает бекэнды, фронтэнд должен написать пользователь
* У MSM есть методы
  * ``current_state`` для получения текущего состояния
  * ``process_event`` для переключения состояния
* Класс ``msm::front::state<>`` служит для полного определения состояний
* Класс ``msm::front::state_machine`` позволяет определять машину состояний

.. code:: cpp

    struct play {};
    struct open_close {};
    struct stop {};
    // ...

    class player : public state_machine<player>
    {
        enum states { Empty, Open, Stopped, Playing, Paused , initial_state = Empty };

        void start_playback(play const&) { std::cout << "player::start_playback\n"; }
        void open_drawer(open_close const&) { std::cout << "player::open_drawer\n"; }
        // ...

        struct transition_table : mpl::vector<
        //    Start     Event        Target      Action                      Guard
        //   +---------+------------+-----------+---------------------------+----------------------------+
        a_row< Stopped , play       ,  Playing  , &player_::start_playback                               >,
        a_row< Stopped , open_close ,  Open     , &player_::open_drawer                                  >,
         _row< Stopped , stop       ,  Stopped                                                           >,
        //   +---------+------------+-----------+---------------------------+----------------------------+
        a_row< Open    , open_close ,  Empty    , &player_::close_drawer                                 >,
        //   +---------+------------+-----------+---------------------------+----------------------------+
        a_row< Empty   , open_close ,  Open     , &player_::open_drawer                                  >,
          row< Empty   , cd_detected,  Stopped  , &player_::store_cd_info   , &player_::good_disk_format >,
          row< Empty   , cd_detected,  Playing  , &player_::store_cd_info   , &player_::auto_start       >,
        //   +---------+------------+-----------+---------------------------+----------------------------+
        a_row< Playing , stop       ,  Stopped  , &player_::stop_playback                                >,
        a_row< Playing , pause      ,  Paused   , &player_::pause_playback                               >,
        a_row< Playing , open_close ,  Open     , &player_::stop_and_open                                >,
        //   +---------+------------+-----------+---------------------------+----------------------------+
        a_row< Paused  , end_pause  ,  Playing  , &player_::resume_playback                              >,
        a_row< Paused  , stop       ,  Stopped  , &player_::stop_playback                                >,
        a_row< Paused  , open_close ,  Open     , &player_::stop_and_open                                >
        //   +---------+------------+-----------+---------------------------+----------------------------+
        > {};

        /*template<class Event, class Fsm>
        void no_transition(const Event& e, Fsm& fsm, int state)
        {
            std::cout << "no transition from state " << state << " on event " << typeid(e).name() << std::endl;
        }*/
    };

    player my_player;
    my_player.process_event(open_close{});
    my_player.process_event(open_close{});
    my_player.process_event(play{});
    std::cout << my_player.current_state() << std::endl;
