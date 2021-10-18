#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/dll/runtime_symbol_info.hpp>

namespace bg = boost::log;

void init()
{
    auto exe_path = boost::dll::program_location();

    bg::add_file_log
    (
        bg::keywords::file_name=exe_path.parent_path() / "sample_%N.log", // <1>
        bg::keywords::rotation_size=10 * 1024 * 1024, // <2>
        bg::keywords::time_based_rotation=bg::sinks::file::rotation_at_time_point(0, 0, 0), // <3>
        bg::keywords::format="[%TimeStamp%]: %Message%" // <4>
    );

    bg::core::get()->set_filter(bg::trivial::severity >= bg::trivial::info);

    bg::add_common_attributes(); // <5>
}

int main()
{
    init();

    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
}
