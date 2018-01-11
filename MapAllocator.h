#pragma once
#include <iostream>

#include <cstddef>
#include <new>
#include <utility>
#include <limits>
#include <array>
#include <vector>
#include <memory>
#include <assert.h>

template <class T, std::size_t size>
class Chunk
{
public:
    using pointer = T*;
    using array_type = std::array<T, size>;

    std::size_t getAvailableSpace() const noexcept
    {
        return size - current - 1;
    }
    pointer getAvailableElem(std::size_t n) noexcept
    {
        if(current >= size)
            return nullptr;
        auto ptrElem = &array[current];
        current += n;
        return ptrElem;
    }

    inline bool isOwned(pointer p) const noexcept
    {
        if(p >= &array[0] && p <= &array[size-1])
            return true;
        return false;
    }

    void free(pointer ptr, std::size_t n)
    {
        for(std::size_t i = 0; i < array.size(); i++)
        {
            if(&array[i] == ptr && ((i+n) == current) )
            {
                current -= n;
                break;
            }
        }
    }

private:
    array_type array;
    std::size_t current = 0;
};

template <class T, std::size_t size = 10>
class MyPool
{
public:
    using pointer = T*;

    MyPool()
    {
        chunk_pool.emplace_back(std::make_unique<Chunk<T, size> >());
    }

    pointer GetNext(std::size_t n)
    {
        assert(n <= size);
        if(chunk_pool.size())
        {
            if(n <= chunk_pool[chunk_pool.size()-1]->getAvailableSpace())
            {
                return chunk_pool[chunk_pool.size()-1]->getAvailableElem(n);
            }
            else
            {
                chunk_pool.emplace_back(std::make_unique<Chunk<T, size> >());
                GetNext(n);
            }
        }
        else
        {
            chunk_pool.emplace_back(std::make_unique<Chunk<T, size> >());
            GetNext(n);
        }
    }

    void Free(pointer ptr, std::size_t n)
    {
        for(auto& pool : chunk_pool)
        {
            if(pool->isOwned(ptr))
            {
                pool->free(ptr, n);
                break;
            }
        }
    }

private:
    std::vector<std::unique_ptr<Chunk<T, size> > > chunk_pool;
};

template <class T> class CustomAllocator;

// Description:
// Specialize for void
template <> class CustomAllocator<void>
{
public:
    using pointer = void*;
    using const_pointer = const void*;
    using value_type = void;

    template <class U>
    struct rebind
    {
        using other = CustomAllocator<U>;
    };
};

template <class T>
class CustomAllocator
{
public:
    // Description:
    // Typedefs
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
        using other = CustomAllocator<U>;
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

    pointer address(reference r) const { return &r; }
    const_pointer address(const_reference r) const { return &r; }

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
    MyPool<value_type> myPool;
};

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
