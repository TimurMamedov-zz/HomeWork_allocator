#pragma once
#include <cstddef>
#include <new>
#include <utility>
#include <limits>
#include <array>
#include <memory>

template <class T, std::size_t size = 5>
class MyPool
{
public:
    using pointer = T*;

    MyPool()
    {
        array = std::make_unique<std::array<std::pair<bool ,T>, size> >();
        for(auto& elem: array)
        {
            elem.first = true;
        }
    }

    pointer GetNext(std::size_t n)
    {
        std::size_t count = 0;
        std::size_t max_count = count;
        std::size_t index = 0;
        for(std::size_t i = 0; i < array->size(); i++)
        {
            if(array->at(i).first)
            {
                count++;
                if(max_count < count)
                {
                    max_count = count;
                    index = i;
                }
            }
            else
            {
                count = 0;
                index++;
            }
        }
        if(n > max_count)
            return nullptr;
        for(std::size_t i = 0; i <= n; i++)
        {

        }
        return &(*array)[count];
    }

    void Free(pointer ptr, std::size_t n)
    {

    }

    inline size_t getSize()
    {
        return array.size();
    }

private:
    std::unique_ptr<std::array<std::pair<bool ,T>, size> > array;
};

template <class T> class MapAllocator;

// Description:
// Specialize for void
template <> class MapAllocator<void>
{
public:
    using pointer = void*;
    using const_pointer = const void*;
    using value_type = void;

    template <class U>
    struct rebind
    {
        using other = MapAllocator<U>;
    };
};

template <class T>
class MapAllocator
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

    // Description:
    // The rebind member allows a container to construct an allocator for some arbitrary type out of
    // the allocator type provided as a template parameter.
    template <class U>
    struct rebind
    {
        using other = MapAllocator<U>;
    };

    // Description:
    // Constructors
    MapAllocator()
    {
        unique_pool = std::make_unique<MyPool<value_type> >();
    }
    MapAllocator( const MapAllocator& other )
    {
        unique_pool = std::make_unique<MyPool<value_type> >();
    }
    template <class U>
    MapAllocator(const MapAllocator<U>&)
    {
        unique_pool = std::make_unique<MyPool<value_type> >();
    }

    // Description:
    // Destructor
    ~MapAllocator() {}

    // Description:
    // Returns the address of r as a pointer type. This function and the following function are used
    // to convert references to pointers.
    pointer address(reference r) const { return &r; }
    const_pointer address(const_reference r) const { return &r; }

    // Description:
    // Allocate storage for n values of T.
    pointer allocate( size_type n, MapAllocator<void>::const_pointer hint = 0 )
    {
        // I would never do it that way:
        //pointer return_value = reinterpret_cast<pointer>( pool.GetNext() );
        // I would prefer to use the got size to allocate:
        pointer return_value = reinterpret_cast<pointer>( unique_pool->GetNext(n) );
        if ( return_value == nullptr )
            throw std::bad_alloc();
        return return_value;
    }

    // Description:
    // Deallocate storage obtained by a call to allocate.
    void deallocate(pointer p, size_type n)
    {
            unique_pool->Free(p, n);
    }

    // Description:
    // Return the largest possible storage available through a call to allocate.
    size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

    template <typename ...Args>
    void construct(pointer ptr, Args&&... args)
    {
        new(ptr)value_type(std::forward<Args>(args)...);
    }

    // Description:
    // Call the destructor on the value pointed to by p
    void destroy(pointer p)
    {
        p->~T();
    }
private:
    std::unique_ptr<MyPool<value_type> > unique_pool;
};

// Return true if allocators b and a can be safely interchanged. "Safely interchanged" means that b could be
// used to deallocate storage obtained through a and vice versa.
template <class T1, class T2>
bool operator == ( const MapAllocator<T1>& lhs, const MapAllocator<T2>& rhs) noexcept
{
    return true;
}
// Return false if allocators b and a can be safely interchanged. "Safely interchanged" means that b could be
// used to deallocate storage obtained through a and vice versa.
template <class T1, class T2>
bool operator != ( const MapAllocator<T1>& lhs, const MapAllocator<T2>& rhs) noexcept
{
    return false;
}
