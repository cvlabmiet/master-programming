#include <iostream>
#include <string>

#include <boost/spirit/home/x3.hpp>

int main()
{
    namespace x3 = boost::spirit::x3;

    std::string_view text{R"(foo: bar,
        gorp : smart ,
        falcou : "crazy frenchman",
        name:sam)"};

    auto name = x3::rule<class name, std::string>{} // явное прописывание тэга и атрибута
              = x3::alpha >> *x3::alnum; // переменные в C-стиле
    auto quote = x3::lexeme['"' >> *~x3::char_('"') >> '"']; // строковые значения в кавычках

    auto it = text.begin();
    bool parsed = x3::phrase_parse(it, text.end(),
                                   (name >> ':' >> (quote | name)) % ',',
                                   x3::space);

    std::cout << "Is parsed: " << std::boolalpha << parsed << "\n"
              << "Position: " << std::distance(text.begin(), it) << " == " << text.size() << "\n";
}
