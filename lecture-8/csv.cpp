#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/spirit/home/x3.hpp>
#include <boost/range/adaptor/indexed.hpp>

/* An example of CSV:
 *      kind,of,header
 *      abc,with space,"quote"
 *      "comma , inside",132,  spaces  dot
 *
 * CSV (comma separated value) EBNF appr. specification (http://www.rfc-editor.org/rfc/rfc4180.txt)
 *      string := [^,\n]+
 *      qstring := " [^"]* "
 *      cell := qstring | string
 *      row := cell (, cell)* \n
 *      csv := row+
 */

namespace types::csv
{
    using csv = std::vector<std::vector<std::string>>;
}

namespace parser::csv
{
    namespace x3 = boost::spirit::x3;

    const auto string = x3::lexeme[+~x3::char_(",\n")];
    const auto qstring = x3::lexeme['"' >>  *(('\\' >> x3::char_) | ~x3::char_("\"")) >> '"'];
    const auto cell = qstring | string;
    const auto row = x3::rule<class row, std::vector<std::string>>{}
                   = (cell % ',') >> x3::no_skip[x3::eol];
    const auto csv = x3::rule<class csv, types::csv::csv>{}
                   = +row;

    template<class Container>
    auto parse(const Container& cnt)
    {
        types::csv::csv result;
        auto it = cnt.begin();
        if (!x3::phrase_parse(it, cnt.end(), csv, x3::ascii::space, result))
            throw std::runtime_error("Invalid input data");

        if (it != cnt.end())
            throw std::out_of_range("Parsing is not complete");

        return result;
    }
}

int main()
{
    std::string csv_data = R"(
        kind,of,header
        abc,with space,"quote"
        "comma , inside",132,  spaces  dot
        new text, quote \"escaped,   "   similar\"  "
        empty,"",""
    )";

    auto result = parser::csv::parse(csv_data);
    for (const auto& row : result | boost::adaptors::indexed())
    {
        std::cout << "Row #" << row.index() << ":";
        for (const auto& cell : row.value() | boost::adaptors::indexed())
            std::cout << " F#" << cell.index() << ": [" << cell.value() << "]";

        std::cout << "\n";
    }
}
