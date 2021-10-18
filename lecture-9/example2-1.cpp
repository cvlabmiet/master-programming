#include <iostream>

#include <boost/format.hpp>

int main()
{
    std::cout << boost::format("%|1$#x| %2% %1%\n") % 123 % 456 << std::endl;
}
