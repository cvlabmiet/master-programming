#include <iostream>
#include <sstream>

#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class animal
{
public:
    animal(int legs = 0) : legs_{legs} {}
    int legs() const { return legs_; }

private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/) { ar & legs_; }

    int legs_;
};

class bird : public animal
{
public:
    bird(bool can_fly = true) : animal{2}, can_fly_{can_fly} {}
    bool can_fly() const { return can_fly_; }

private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar & boost::serialization::base_object<animal>(*this);
        ar & can_fly_;
    }

    bool can_fly_;
};

int main()
{
    std::stringstream ss;

    auto serialize = [](auto& os, const bird& obj) {
        boost::archive::text_oarchive oa{os};
        oa << obj;
    };

    auto deserialize = [](auto& is) {
        boost::archive::text_iarchive ia{is};
        bird obj;
        ia >> obj;
        return obj;
    };

    bird penguin{false};
    serialize(ss, penguin);

    bird b = deserialize(ss);
    std::cout << b.legs() << " " << std::boolalpha << b.can_fly() << std::endl;
}
