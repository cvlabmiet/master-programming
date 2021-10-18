#include <algorithm>
#include <array>
#include <iostream>
#include <experimental/iterator>

#include <boost/multi_array.hpp>

int main()
{
    boost::multi_array<double, 3> a{boost::extents[3][6][8]};
    a[0][0][7] = 3.14;
    a(std::array{1, 1, 7}) = 2.718;

    using range = boost::multi_array_types::index_range;
    using index = range::index;
    auto view = a[boost::indices[range()][range() < index(5)][index(4) <= range().stride(2) <= index(7)]];

    for (auto v1 : view)
        for (auto v2 : v1)
            for (auto& x : v2)
                x = 77;

    for (const auto& v1 : a)
    {
        for (const auto& v2 : v1)
        {
            std::copy(v2.begin(), v2.end(), std::experimental::make_ostream_joiner(std::cout, ", "));
            std::cout << "\n";
        }

        std::cout << "\n";
    }
}
