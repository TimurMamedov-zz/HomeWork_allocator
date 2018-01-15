#include <iostream>
#include <map>

#include "CustomAllocator.h"
#include "functions.h"

int main(int argc, char const *argv[])
{
    try
    {
        std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, std::uint64_t> > > map;
        for(std::uint64_t i = 0; i < 10; i++)
            map.emplace(i, fac(i));

        for(const auto& elem : map)
        {
           std::cout << elem.first << " " << elem.second << "\n";
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
