#include <algorithm>
#include <iostream>
#include <iterator>

#include <boost/heap/binomial_heap.hpp>

int main()
{
    boost::heap::binomial_heap<int> bh;
    bh.push(2);
    bh.push(3);
    bh.push(1);

    boost::heap::binomial_heap<int> bh2;
    bh2.push(4);
    bh.merge(bh2);

    std::copy(bh.ordered_begin(), bh.ordered_end(), std::ostream_iterator<int>(std::cout, "\n"));
}
