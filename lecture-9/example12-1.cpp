#include <iostream>
#include <string>
#include <tuple>

#include <boost/coroutine2/coroutine.hpp>

int main()
{
    namespace bc2 = boost::coroutines2;

    auto cooperative = [](bc2::coroutine<std::tuple<int, std::string>>::pull_type &source) {
        auto args = source.get();
        std::cout << "first = " << std::get<0>(args) << " " << std::get<1>(args) << "\n";
        source();
        args = source.get();
        std::cout << "second = " << std::get<0>(args) << " " << std::get<1>(args) << "\n";
    };

    bc2::coroutine<std::tuple<int, std::string>>::push_type sink{cooperative};
    std::cout << "start: ";
    sink(std::make_tuple(0, "aaa"));
    std::cout << "next: ";
    sink(std::make_tuple(1, "bbb"));
    std::cout << "end\n";
}
