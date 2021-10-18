#include <iostream>
#include <vector>
#include <string>

#include <boost/dynamic_bitset.hpp>

int main()
{
    boost::dynamic_bitset<uint32_t> db(std::string("11010110101"));

    std::vector<uint32_t> v{{8, 779, 65564, 5321, 556}};
    db.append(v.begin(), v.end());
    db.push_back(true);
    db.append(4485);

    std::cout.setf(std::ios::boolalpha);
    std::cout << db.size() << '\n';
    std::cout << db.count() << '\n';
    std::cout << db.any() << '\n';
    std::cout << db.none() << '\n';

    std::cout << db[0].flip() << '\n';
    std::cout << ~db[3] << '\n';

    std::vector<uint32_t> out;
    boost::to_block_range(db, std::back_inserter(out));
    for (auto x : out)
        std::cout << x << "\n";
}
