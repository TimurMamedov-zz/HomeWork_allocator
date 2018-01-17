#include <iostream>
#include <map>

#include "CustomAllocator.h"
#include "functions.h"
#include "CustomContainer.h"

int main(int argc, char const *argv[])
{
    try
    {
        std::map<int, int> map;
        for(std::uint64_t i = 0; i < 10; i++)
            map.emplace(i, fac(i));

        std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, std::uint64_t> > > map_with_custom_alloc;
        for(std::uint64_t i = 0; i < 10; i++)
            map_with_custom_alloc.emplace(i, fac(i));

        for(const auto& elem : map_with_custom_alloc)
        {
           std::cout << elem.first << " " << elem.second << "\n";
        }

        CustomContainer<int> customContainer;
        for(std::uint64_t i = 0; i < 10; i++)
            customContainer.push_back(i);

        CustomContainer<int, CustomAllocator<int> > customContainer_with_custom_alloc;
        for(std::uint64_t i = 0; i < 10; i++)
            customContainer_with_custom_alloc.push_back(i);

        for(const auto& elem : customContainer_with_custom_alloc)
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
