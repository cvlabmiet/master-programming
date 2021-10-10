#include <iostream>
#include <list>
#include <tuple>
#include <vector>

struct sfinae
{
private:
    template<class U>
    constexpr static bool f(typename U::value_type*)
    {
        return true;
    }

    template<class U>
    constexpr static bool f(...)
    {
        return false;
    }

public:
    template<class T>
    constexpr static bool is_container = f<T>(nullptr);
};

int main()
{
    std::cout << std::boolalpha;

    auto types = std::make_tuple(std::vector<int>{}, std::list<double>{}, int{}, static_cast<const char*>(nullptr));
    std::apply([](auto... xs) {
        ((std::cout << "Is a container? " << sfinae::is_container<decltype(xs)> << "\n"), ...);
    }, types);
}
