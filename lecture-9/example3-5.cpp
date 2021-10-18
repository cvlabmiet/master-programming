#include <iostream>

#include <boost/intrusive/list.hpp>

int main()
{
    struct animal : public boost::intrusive::list_base_hook<boost::intrusive::link_mode<boost::intrusive::auto_unlink>>
    {
        std::string name;
        int legs;

        animal(std::string name, int legs) : name(std::move(name)), legs(legs)
        {}
    };

    animal a1{"cat", 4};
    animal a2{"ostrich", 2};
    animal *a3 = new animal{"spider", 8};

    boost::intrusive::list<animal, boost::intrusive::constant_time_size<false>> animals;

    animals.push_back(a1);
    animals.push_back(a2);
    animals.push_back(*a3);

    delete a3;

    for (const animal &a : animals)
        std::cout << a.name << '\n';
}
