#include <iostream>
#include <string>
#include <vector>

#include <boost/flyweight.hpp>

struct person
{
    struct country {};

    int id;
    boost::flyweight<std::string> city;
    boost::flyweight<std::string, boost::flyweights::tag<country>> country;

    person(int id, std::string city, std::string country)
        : id{id}, city{std::move(city)}, country{std::move(country)} {}
};

int main()
{
    std::vector<person> persons;
    for (int i = 0; i < 100000; ++i)
        persons.push_back({i, "Berlin", "Germany"});

    std::cout << "100th: " << persons[100].city << " " << &persons[100].city.get() << "\n"
              << "200th: " << persons[200].city << " " << &persons[200].city.get() << "\n";
}
