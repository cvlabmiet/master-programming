#include <iostream>

#include <boost/signals2.hpp>

int main()
{
    boost::signals2::signal<void()> s;

    auto hello = [] {
        std::cout << "Hello, world!" << std::endl;
    };

    auto disconnect = [&s, hello] {
        s.disconnect(hello);
    };

    s.connect(hello);
    s.connect(disconnect);
    s();
    s();
}
