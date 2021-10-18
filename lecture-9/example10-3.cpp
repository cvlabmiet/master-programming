#include <algorithm>
#include <iostream>
#include <string>

#include <boost/mpi.hpp>

int main(int argc, char* argv[])
{
    boost::mpi::environment env{argc, argv};
    boost::mpi::communicator world;

    std::string s = "Hello, others!";
    if (world.rank() == 0)
        s = "Hello, world!";
    else if (world.rank() == 1)
        s = "Hello, moon!";
    else if (world.rank() == 2)
        s = "Hello, sun!";

    std::cout << "I am process " << world.rank()
              << " on " << world.size() << ", my value is [" << s << "]\n";

    std::string result;
    boost::mpi::reduce(world, s, result, [](const auto&... xs) { return std::min(xs...); }, 0);
    if (world.rank() == 0)
        std::cout << "The alphabet lowest output is [" << result << "]\n";
}
