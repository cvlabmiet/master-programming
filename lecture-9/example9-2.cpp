#include <algorithm>
#include <iostream>
#include <vector>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>

int main()
{
    std::vector v{{1, 3, 2}};
    std::for_each(v.begin(), v.end(),
        boost::lambda::if_then(boost::lambda::_1 > 1, std::cout << boost::lambda::_1 << "\n")
    );
}
