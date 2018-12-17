#include <iostream>
#include <string>
#include <vector>

#include <boost/gil/extension/io/png.hpp>
#include <cxxopts.hpp>

#include "imgproc.hpp"

int main(int argc, char** argv)
{
    namespace bg = boost::gil;

    cxxopts::Options options(argv[0], "An image processing example. Version " + imgproc::version.to_string());
    options
        .positional_help("input images")
        .add_options()
        ("h,help", "show help")
        ("v,version", "show version")
        ("t,transform", "use transform matrix", cxxopts::value<bool>())
        ("s,histogram", "create histogram of an image", cxxopts::value<bool>())
        ("o,output", "output image", cxxopts::value<std::string>()->default_value("/dev/null"))
        ("inputs", "input images", cxxopts::value<std::vector<std::string>>());
    options.parse_positional("inputs");
    auto args = options.parse(argc, argv);

    if (args.count("help"))
    {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (args.count("version"))
    {
        std::cout << "Version " << imgproc::version.to_string() << std::endl;
        return 0;
    }

    if (args.count("inputs") < 1)
    {
        std::cerr << "I need 2 images at least." << std::endl;
        return -1;
    }

    const auto& inputs = args["inputs"].as<std::vector<std::string>>();

    bg::gray8_image_t img0;
    bg::read_and_convert_image(inputs[0], img0, bg::png_tag{});

    if (args.count("transform"))
    {
        auto img = imgproc::transform(bg::const_view(img0));
        bg::write_view(args["output"].as<std::string>(), bg::const_view(img), bg::png_tag{});
    }
    else if (args.count("histogram"))
    {
        auto hist = imgproc::histogram(bg::const_view(img0));
        auto img = imgproc::bar(hist);
        bg::write_view(args["output"].as<std::string>(), bg::const_view(img), bg::png_tag{});
    }
    else
    {
        std::cerr << "Specify transformation action." << std::endl;
        return -1;
    }

    return 0;
}
