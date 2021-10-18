#include <iostream>
#include <regex>

int main()
{
    std::string s = "Boost Libraries";
    std::regex expr{R"((\w+)\s*(\w+))"};
    if (std::smatch what; std::regex_search(s, what, expr))
    {
        std::cout << what[0] << '\n';
        std::cout << what[1] << "_" << what[2] << '\n';
    }
}
