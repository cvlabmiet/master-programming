#include <iostream>
#include <tuple>
#include <utility>

template<class Stream, class Tuple, size_t... Is>
Stream& func_impl(Stream& os, const Tuple& t, std::index_sequence<Is...>)
{
    return (os << ... << std::get<Is>(t));
}

/*template<class Stream, class... Ts>
Stream& func1(Stream& os, const std::tuple<Ts...>& t)
{
    func_impl(os, t, std::index_sequence_for<Ts...>{});
}*/

template<class Stream, class Tuple>
Stream& func2(Stream& os, const Tuple& t)
{
    return func_impl(os, t, std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

template<class... Ts>
std::ostream& operator<<(std::ostream& os, const std::tuple<Ts...>& t)
{
    // return std::apply([&os](const auto&... xs) -> decltype(auto) { return (os << ... << xs); }, t);
    return func2(os, t);
}

int main()
{
    std::cout << std::tuple{1, ' ', 2.3, ' ', "lala"} << "\n";
}
