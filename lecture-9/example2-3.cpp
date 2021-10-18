#include <iostream>
#include <iterator>
#include <string>

#include <boost/xpressive/xpressive.hpp>
#include <boost/xpressive/regex_actions.hpp>

int main()
{
    namespace xpr = boost::xpressive;

    std::string s{"Boost Libraries"};
    auto r = xpr::sregex::compile(R"(\w+\s*\w+)");
    xpr::sregex r2 = +xpr::_w >> xpr::_s >> +xpr::_w;
    std::cout << xpr::regex_match(s, r) << " == " << xpr::regex_match(s, r2) << std::endl;

    std::ostream_iterator<std::string> it{std::cout, "\n"};
    xpr::sregex r3 = (+xpr::_w)[*xpr::ref(it) = xpr::_] >> xpr::_s >> +xpr::_w;
    std::cout << std::boolalpha << xpr::regex_match(s, r3) << std::endl;
}
