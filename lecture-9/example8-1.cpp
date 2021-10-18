#include <iostream>

#include <boost/date_time/gregorian/gregorian.hpp>

int main()
{
    namespace bg = boost::gregorian;

    bg::date d{2018, 11, 19};
    bg::months ms{1};
    bg::date d2 = d + ms;
    bg::date d3 = d2 - ms;
    std::cout << d2 << " vs. " << d3 << std::endl;
}
