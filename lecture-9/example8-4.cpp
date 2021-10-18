#include <iostream>
#include <cmath>

#include <boost/timer/timer.hpp>

int main()
{
    boost::timer::auto_cpu_timer timer;
    for (int i = 0; i < 1000000; ++i)
        std::pow(1.234, i);

    std::cout << "Done\n";
}
