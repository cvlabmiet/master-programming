#include <iostream>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    namespace bp = boost::posix_time;
    namespace bg = boost::gregorian;

    bp::ptime pt{bg::date{2014, 5, 12}, bp::time_duration{12, 0, 0}};
    bp::time_iterator it{pt, bp::time_duration{6, 30, 0}};
    std::cout << *++it << "\n" << *++it << std::endl;
}
