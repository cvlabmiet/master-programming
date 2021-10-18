#include <fstream>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>

int main(int argc, char** argv)
{
    namespace po = boost::program_options;

    po::options_description generalOptions{"General"};
    generalOptions.add_options()
        ("help,h", "Help screen")
        ("config", po::value<std::string>()->default_value("/etc/config.cfg"), "Config file")
        ("age", po::value<int>(), "Age");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, generalOptions), vm);
    if (vm.count("config"))
    {
        std::ifstream ifs{vm["config"].as<std::string>()};
        if (ifs)
            po::store(po::parse_config_file(ifs, generalOptions), vm);
    }
    po::notify(vm);

    if (vm.count("help"))
        std::cout << generalOptions << std::endl;
    else if (vm.count("age"))
        std::cout << "Your age is: " << vm["age"].as<int>() << std::endl;
}
