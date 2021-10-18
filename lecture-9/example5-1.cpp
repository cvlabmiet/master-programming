#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/gather.hpp>

int main()
{
    namespace ba = boost::algorithm;

    std::cout << ba::unhex(std::string("432b2b")) << '\n';
    ba::hex(std::vector<char>{'C', '+', '+'}, std::ostream_iterator<char>(std::cout, ""));
    std::cout << "\n";

    std::vector v{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
    auto p = ba::gather(v.begin(), v.end(), v.begin() + 4, [](auto x) { return x % 2 == 0; });
    for (auto it = p.first; it != p.second; ++it)
        std::cout << *it << " ";

    std::cout << "\n";
}
