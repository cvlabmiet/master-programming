#include <iostream>
#include <string>
#include <stdexcept>

#include <boost/exception/all.hpp>

int main()
{
    using errmsg_info = boost::error_info<struct tag_errmsg, std::string>;

    try
    {
        try
        {
            BOOST_THROW_EXCEPTION(std::runtime_error{"123"});
        }
        catch (const boost::exception& e)
        {
            e << errmsg_info{"writing lots of zeros failed"};
            throw;
        }
    }
    catch (const boost::exception& e)
    {
        std::cerr << *boost::get_error_info<errmsg_info>(e);
        std::cerr << boost::diagnostic_information(e);
    }
}
