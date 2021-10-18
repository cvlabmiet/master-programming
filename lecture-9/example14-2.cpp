#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

int main()
{
    try
    {
        int i = 0x10000;
        short s = boost::numeric_cast<short>(i);
        std::cout << s << std::endl;
    }
    catch (boost::numeric::bad_numeric_cast &e)
    {
        std::cout << e.what() << std::endl;
    }
}
