#include <iostream>
#include <string>

#include <boost/bimap.hpp>
#include <boost/bimap/support/lambda.hpp>

int main()
{
    boost::bimap<std::string, boost::bimaps::unconstrained_set_of<int>> animals;

    animals.insert({"cat", 4});
    animals.insert({"shark", 0});
    animals.insert({"spider", 8});

    auto it = animals.left.find("cat");
    animals.left.modify_key(it, boost::bimaps::_key = "dog");

    for (const auto& [key, val] : animals)
        std::cout << key << ":" << val << "\n";
}
