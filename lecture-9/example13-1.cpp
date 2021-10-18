#include <iostream>
#include <system_error>

int main()
{
    try
    {
        throw std::system_error{std::make_error_code(std::errc::not_supported)};
    }
    catch (const std::system_error& e)
    {
        std::error_code ec = e.code();
        std::cerr << ec.value() << '\n';
        std::cerr << ec.category().name() << std::endl;
    }
}
