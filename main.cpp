#include <iostream>
#include <map>

#include "CustomAllocator.h"
#include "functions.h"
#include "CustomContainer.h"

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

        CustomContainer<int> list;
        for(std::uint64_t i = 0; i < 11; i++)
            list.push_back(i);

        for(const auto& elem : list)
        {
           std::cout << elem << "\n";
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
