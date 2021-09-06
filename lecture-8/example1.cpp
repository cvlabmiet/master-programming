#include <iostream>
#include <string>

#include <boost/spirit/home/x3.hpp>

int main()
{
    namespace x3 = boost::spirit::x3;

    std::string_view text{"123 45.6"};
    bool parsed = x3::parse(text.begin(), text.end(), x3::int_ >> ' ' >> x3::double_);

    std::cout << "Parsed value is " << std::boolalpha << parsed << "\n";
}
