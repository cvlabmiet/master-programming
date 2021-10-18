#include <iostream>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

int main()
{
    namespace bi = boost::interprocess;

    bi::shared_memory_object shdmem{bi::open_or_create, "Boost", bi::read_write};
    shdmem.truncate(1024);
    bi::mapped_region region{shdmem, bi::read_write};
    int *i1 = static_cast<int*>(region.get_address());
    *i1 = 99;

    bi::mapped_region region2{shdmem, bi::read_only};
    int *i2 = static_cast<int*>(region2.get_address());
    std::cout << *i2 << std::endl;
}
