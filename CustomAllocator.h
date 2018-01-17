#pragma once
#include "ChunkPool.h"

template <class T, std::size_t size> class CustomAllocator;

template <> class CustomAllocator<void, 10>
{
public:
    using pointer = void*;
    using const_pointer = const void*;
    using value_type = void;

    template <class U>
    struct rebind
    {
        using other = CustomAllocator<U, 10>;
    };
};
//----------------------------------------------------
template <class T, std::size_t size = 10>
class CustomAllocator
{
public:
    using value_type = T;
    using size_type = std::size_t ;
    using difference_type = std::ptrdiff_t ;
    using pointer = T* ;
    using const_pointer = const T* ;
    using reference = T& ;
    using const_reference = const T& ;

    template <class U>
    struct rebind
    {
        using other = CustomAllocator<U, size>;
    };

    CustomAllocator()
    {
    }
    CustomAllocator( const CustomAllocator& other )
    {
    }
    template <class U>
    CustomAllocator(const CustomAllocator<U>&)
    {
    }

    ~CustomAllocator() {}

    pointer address(reference r) const noexcept { return &r; }
    const_pointer address(const_reference r) const noexcept { return &r; }

    pointer allocate( size_type n, CustomAllocator<void>::const_pointer hint = 0 )
    {
        pointer return_value = reinterpret_cast<pointer>( myPool.GetNext(n) );
        if ( return_value == nullptr )
            throw std::bad_alloc();
        return return_value;
    }

    void deallocate(pointer p, size_type n)
    {
        myPool.Free(p, n);
    }

    size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

    template <typename ...Args>
    void construct(pointer ptr, Args&&... args)
    {
        new(ptr)value_type(std::forward<Args>(args)...);
    }

    void destroy(pointer p)
    {
        p->~T();
    }

private:
    ChunkPool<value_type, size> myPool;
};
//-----------------------------------------------------------
template <class T1, class T2>
bool operator == ( const CustomAllocator<T1>& lhs, const CustomAllocator<T2>& rhs) noexcept
{
    return true;
}

template <class T1, class T2>
bool operator != ( const CustomAllocator<T1>& lhs, const CustomAllocator<T2>& rhs) noexcept
{
    return false;
}
