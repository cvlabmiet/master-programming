#include <iostream>
#include <string>

#include <boost/tokenizer.hpp>

int main()
{
    std::string_view s{"Boost C++ Libraries"};
    boost::char_separator<char> sep{" ", "+", boost::keep_empty_tokens};
    boost::tokenizer tok{s, sep};
    for (const auto& t : tok)
        std::cout << t << '\n';
}
