#include <iostream>

#include <boost/cast.hpp>

struct base1 { virtual ~base1() = default; };
struct base2 { virtual ~base2() = default; };
struct derived : public base1, public base2 {};

void downcast(base1 *b1)
{
    derived* d = boost::polymorphic_downcast<derived*>(b1);
    std::cout << d << "\n";
}

void crosscast(base1 *b1)
{
    base2* b2 = boost::polymorphic_cast<base2*>(b1);
    std::cout << b2 << "\n";
}

int main()
{
    derived* d = new derived;
    downcast(d);

    base1* b1 = new derived;
    crosscast(b1);
}
