RAII и управление памятью
=========================

Умные указатели
---------------

* `boost/smart_ptr/ <https://www.boost.org/libs/smart_ptr>`_
* Единоличное владение ``boost::scoped_ptr`` (эквивалент ``std::unique_ptr``)
* Общее владение ``boost::shared_ptr`` (аналог ``std::shared_ptr``)
* Слабый указатель ``boost::weak_ptr`` (аналог ``std::weak_ptr``)

.. code:: cpp

    auto sp = std::make_shared<T>(123, "abc");
    std::weak_ptr wp{sp};
    std::shared_ptr<T> sh = wp.lock();
    if (sh)
        std::cout << sh->str;

Адаптации:

* ``scoped_array`` --- ``scoped_ptr`` для массивов
* ``intrusive_ptr`` --- счётчик ссылок находится в самом объекте
  * необходимо перегрузить функции ``intrusive_ptr_add_ref`` и ``intrusive_ptr_release`` для своего типа
* ``shared_array`` --- ``shared_ptr`` для массивов
* ``local_shared_ptr`` --- на каждый поток свой счётчик ссылок
* Всевозможные кастования

Умный контейнер для указателей
------------------------------

* `boost/ptr_container/ <https://www.boost.org/libs/ptr_container>`_
* По функциональности эквивалентен ``std::SomeContainer<std::unique_ptr<T>>``
* Облегчает написание кода

.. code:: cpp

    boost::ptr_set<int> s;
    s.insert(new int{2});
    s.insert(std::make_unique(1));
    std::cout << *s.begin() << '\n';

    std::set<std::unique_ptr<int>, boost::indirect_fun<std::less<int>>> v;
    v.insert(std::make_unique_ptr(2));
    v.insert(std::make_unique_ptr(1));
    std::cout << **v.begin() << '\n';

Автоматическое освобождение ресурсов
------------------------------------

* `boost/scope_exit.hpp <https://www.boost.org/libs/scope_exit>`_
* Автоматическое освобождение ресурсов при выходе из области видимости
* Передача ссылок только необходимых объектов
* Передача ``this``
* Использование ``boost::lambda``
* Эквивалентно написанию своего класса с деструктором и лямбдой в конструкторе

.. code:: cpp

    BOOST_SCOPE_EXIT(&commit, this_) {
        if(!commit)
            this_->persons_.pop_back();
    } BOOST_SCOPE_EXIT_END

    BOOST_SCOPE_EXIT_ALL(&, checkpoint, this) {
        if(checkpoint == p.evolution)
            this->persons_.pop_back();
    };


Пул для работы с памятью
-------------------------

* `boost/pool/ <https://www.boost.org/libs/pool>`_
* Решает вопросы мелких объектов и фрагментации памяти
* Уменьшает задержки на поиски свободного фрагмента для выделения памяти
* ``simple_segregated_storage`` --- замена ``std::malloc`` с разбиением памяти на сегменты
* ``object_pool`` --- автоматически резервирует память под объекты. Основан на ``simple_segregated_storage``
* ``singleton_pool`` --- похож на ``simple_segregated_storage``, освобождает память всю целиком
* ``pool_allocator`` --- аллокатор, может быть использован в стандартных контейнерах. Необходимо вручную освобождать память аллокатора
* ``fast_pool_allocator`` --- аналогичем ``pool_allocator``, но память может быть не непрерывной. Используется в ``std::list``

.. code:: cpp

    boost::object_pool<int> pool;

    int *i = pool.malloc();
    *i = 1;

    pool.destroy(i);

    boost::simple_segregated_storage<std::size_t> storage;
    std::vector<char> v(42);
    storage.add_block(&v.front(), v.size(), 11);

    int *n = static_cast<int*>(storage.malloc());
    *n = 45;

    storage.free(n);

    std::vector<int, boost::pool_allocator<int>> v{{7, 8, 99}};
    ...
    boost::singleton_pool<boost::pool_allocator_tag, sizeof(int)>::purge_memory();
