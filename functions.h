#pragma once
#include <assert.h>
#include <cstdint>
#include <iostream>

template<std::size_t N>
struct Table
{
    constexpr Table() : t()
    {
        t[0] = 1;
        for (auto i = 1; i < N; ++i)
            t[i] = t[i - 1] * i;
    }
    std::uint64_t t[N];
};

template<typename T>
T fac(T x)
{
    static_assert(sizeof(T) <= sizeof(std::uint64_t), "T is too large");
    constexpr auto table = Table<13>();
    assert(x >= 0);
    return x < 13 ? static_cast<T>(table.t[x]) : 0;
}
