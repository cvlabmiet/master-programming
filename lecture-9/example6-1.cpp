#include <iostream>

#include <boost/asio.hpp>

int main()
{
    using namespace std::literals;

    boost::asio::io_service ioservice;

    boost::asio::steady_timer timer1{ioservice, 3s};
    timer1.async_wait([](auto) { std::cout << "3 sec\n"; });

    boost::asio::steady_timer timer2{ioservice, 4s};
    timer2.async_wait([](auto) { std::cout << "4 sec\n"; });

    ioservice.run();
}
