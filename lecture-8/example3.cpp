#include <iostream>
#include <string>

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

int main()
{
    namespace x3 = boost::spirit::x3;

    std::string_view text1{"pizza"};

    std::string result; // совместимо с атрибутом std::vector<char>
    x3::parse(text1.begin(), text1.end(), *x3::char_, result);

    std::cout << "Result: " << result << "\n";

    std::string_view text2{"cosmic pizza"};

    std::pair<std::string, std::string> presult;
    x3::parse(text2.begin(), text2.end(), *~x3::char_(' ') >> ' ' >> *x3::char_, presult);

    std::cout << "Result of pair: " << presult.first << ", " << presult.second << "\n";
}
