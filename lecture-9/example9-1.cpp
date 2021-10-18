#include <iostream>

#include <boost/phoenix/phoenix.hpp>

int main()
{
    using namespace boost::phoenix::placeholders;

    std::vector v{{1, 2, 3, 4, 5}};
    std::for_each(v.begin(), v.end(), std::cout << arg1 << ",");
}
