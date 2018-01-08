#pragma once
#include <cstddef>
#include <new>
#include <utility>
#include <limits>
#include <array>

template <class T, std::size_t size = 5>
class MyPool
{
public:
    using pointer = T*;

    static MyPool & GetInstance()
    {
        static MyPool retval;
        return retval;
    }

    static pointer GetNext(std::size_t n)
    {
        static std::size_t current = 0;
        if(current >= getSize())
            return nullptr;
        return &array[current++];
    }

    inline size_t getSize()
    {
        return array.size();
    }

private:
    MyPool();
    static std::array<T, size> array;
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
    template <class U1> struct rebind { using other = MapAllocator<U1>; };
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
    MapAllocator() : pool(MyPool<value_type>::GetInstance()) {}
    MapAllocator( const MapAllocator& other ) : pool(MyPool<value_type>::GetInstance()) {}
    template <class U>
    MapAllocator(const MapAllocator<U>&) : pool(MyPool<value_type>::GetInstance()) {}

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
        pointer return_value = reinterpret_cast<pointer>( pool.GetNext(n) );
        if ( return_value == nullptr )
            throw std::bad_alloc();
        return return_value;
    }

    // Description:
    // Deallocate storage obtained by a call to allocate.
    void deallocate(pointer p, size_type n)
    {
        //    pool.Free(p);
    }

    // Description:
    // Return the largest possible storage available through a call to allocate.
    size_type max_size() const
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
    MyPool<value_type> &pool;
};

// Return true if allocators b and a can be safely interchanged. "Safely interchanged" means that b could be
// used to deallocate storage obtained through a and vice versa.
template <class T1, class T2> bool operator == ( const MapAllocator<T1>& a, const MapAllocator<T2>& b)
{
    return true;
}
// Return false if allocators b and a can be safely interchanged. "Safely interchanged" means that b could be
// used to deallocate storage obtained through a and vice versa.
template <class T1, class T2> bool operator != ( const MapAllocator<T1>& a, const MapAllocator<T2>& b)
{
    return false;
}
