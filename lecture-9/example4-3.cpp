#include <iostream>

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>

int main()
{
    using namespace boost::logic;

    std::cout.setf(std::ios::boolalpha);

    boost::logic::tribool b1 = true;
    std::cout << (b1 || indeterminate) << '\n';
    std::cout << (b1 && indeterminate) << '\n';

    boost::logic::tribool b2 = false;
    std::cout << (b2 || indeterminate) << '\n';
    std::cout << (b2 && indeterminate) << '\n';

    boost::logic::tribool b3 = boost::logic::indeterminate;
    std::cout << (b3 || b3) << '\n';
    std::cout << (b3 && b3) << '\n';
}
