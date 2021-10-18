#include <iostream>

#include <boost/chrono.hpp>

int main()
{
    namespace bc = boost::chrono;

    auto p = bc::process_real_cpu_clock::now();
    std::cout << p << "\n"
              << bc::time_point_cast<bc::minutes>(p) << std::endl;
}
