#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>

int main()
{
    namespace bpt = boost::property_tree;

    bpt::ptree pt;
    pt.put("drive.win.system", "20 files");

    auto c = pt.get_optional<std::string>("drive");
    std::cout << std::boolalpha << c.is_initialized() << '\n';

    pt.put_child("drv.files", bpt::ptree{"50 files"});
    pt.add_child("drv.files", bpt::ptree{"60 files"});

    bpt::ptree d = pt.get_child("drv");
    for (const auto& [key, val] : d)
        std::cout << val.get_value<std::string>() << '\n';

    boost::optional<bpt::ptree&> e = pt.get_child_optional("ala");
    std::cout << e.is_initialized() << std::endl;
}
