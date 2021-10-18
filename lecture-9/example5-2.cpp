#include <iostream>
#include <string>
#include <experimental/iterator>

#include <boost/range/irange.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/istream_range.hpp>

int main()
{
    auto ir = boost::irange(0, 3);
    boost::copy(ir, std::experimental::make_ostream_joiner(std::cout, ", "));
    std::cout << "\n";

    auto sr = boost::istream_range<int>(std::cin);
    boost::copy(sr, std::ostream_iterator<int>{std::cout, "\n"});
}
