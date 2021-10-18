#include <iostream>
#include <utility>

#include <boost/compressed_pair.hpp>

int main()
{
    struct empty {};

    std::pair<int, empty> p;
    boost::compressed_pair<int, empty> cp;
    std::cout << sizeof(p) << " vs. " << sizeof(cp) << std::endl;
}
