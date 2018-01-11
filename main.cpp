#include <iostream>
#include <map>
#include <assert.h>

#include "MapAllocator.h"

template<int N>
struct Table {
    constexpr Table() : t() {
        t[0] = 1;
        for (auto i = 1; i < N; ++i)
            t[i] = t[i - 1] * i;
    }
    std::uint64_t t[N];
};

template<typename T>
T fac(T x) {
    static_assert(sizeof(T) <= sizeof(std::uint64_t), "T is too large");
    constexpr auto table = Table<66>();
    assert(x >= 0);
    return x < 66 ? static_cast<T>(table.t[x]) : 0;
}

int main(int argc, char const *argv[])
{
    try
    {
        std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int> > > map;
        for(std::size_t i = 1; i < 11; i++)
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
