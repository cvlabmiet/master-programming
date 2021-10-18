#include <iostream>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

int main()
{
    boost::uuids::string_generator string_gen;
    boost::uuids::uuid id = string_gen("CF77C981-F61B-7817-10FF-D916FCC3EAA4");
    std::cout << id.variant() << ":" << id.version() << " = " << id << std::endl;
}
