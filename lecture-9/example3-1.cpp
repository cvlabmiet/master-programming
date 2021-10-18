#include <iostream>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>

int main()
{
    struct animal
    {
        std::string name;
        int legs;
    };

    boost::multi_index::multi_index_container<
        animal,
        boost::multi_index::indexed_by<
            boost::multi_index::sequenced<>,
            boost::multi_index::ordered_non_unique<
                boost::multi_index::member<
                    animal, int, &animal::legs
                >
            >,
            boost::multi_index::random_access<>
        >
    > animals;

    animals.emplace_back("cat", 4);
    animals.emplace_back("shark", 0);
    animals.emplace_back("spider", 8);

    auto& legs_index = animals.get<1>();
    auto it = legs_index.find(4);
    legs_index.modify(it, [](animal &a){ a.name = "dog"; });

    for (const auto& x : animals)
        std::cout << x.name << " " << x.legs << "\n";
}
