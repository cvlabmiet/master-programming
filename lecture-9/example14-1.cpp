#include <iostream>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

int main()
{
    namespace ba = boost::accumulators;

    ba::accumulator_set<double, ba::features<ba::tag::mean, ba::tag::variance>, int> acc;
    acc(8, ba::weight=1);
    acc(9, ba::weight=1);
    acc(10, ba::weight=4);
    acc(11, ba::weight=1);
    acc(12, ba::weight=1);
    std::cout << ba::mean(acc) << ":" << ba::variance(acc) << std::endl;
}
