#pragma once
#include <cstddef>
#include <new>
#include <utility>

class MyPool
{
public:
    static MyPool & GetInstance( void )
    {
        static MyPool retval;
        return retval;
    }
private:
    MyPool(void);
};

template <class T1> class MapAllocator;

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

template <class T1> class MapAllocator
{
public:
    // Description:
    // Typedefs
    using value_type = T1;
    using size_type = std::size_t ;
    using difference_type = std::ptrdiff_t ;
    using pointer = T1* ;
    using const_pointer = const T1* ;
    using reference = T1& ;
    using const_reference = const T1& ;

    // Description:
    // The rebind member allows a container to construct an allocator for some arbitrary type out of
    // the allocator type provided as a template parameter.
    template <class U1> struct rebind { typedef MapAllocator<U1> other; };

    // Description:
    // Constructors
    MapAllocator( void ) : pool(MyPool::GetInstance()) {}
    MapAllocator( const MapAllocator& other ) : pool(MyPool::GetInstance()) {}
    template <class U1> MapAllocator(const MapAllocator<U1>&) : pool(MyPool::GetInstance()) {}

    // Description:
    // Destructor
    ~MapAllocator( void ) {}

    // Description:
    // Returns the address of r as a pointer type. This function and the following function are used
    // to convert references to pointers.
    pointer address(reference r) const { return &r; }
    const_pointer address(const_reference r) const { return &r; }

    // Description:
    // Allocate storage for n values of T1.
    pointer allocate( size_type n, MapAllocator<void>::const_pointer hint = 0 )
    {
        // I would never do it that way:
        //pointer return_value = reinterpret_cast<pointer>( pool.GetNext() );
        // I would prefer to use the got size to allocate:
        //    pointer return_value = reinterpret_cast<pointer>( pool.GetNext(n) );
        pointer return_value = nullptr;
        if ( return_value == 0 )
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
        size_type return_value = 0xFFFFFFFF;
        return_value /= sizeof(T1);
        return return_value;
    }

    // Description:
    // Construct an object of type T1 at the location of ptr
    void construct(pointer ptr)
    {
        ::new (reinterpret_cast<void*>(ptr)) T1;
    }

    // Description:
    // Construct an object of type T1 at the location of ptr, using the value of U1 in the call to the
    // constructor for T1.
    template <typename ...Args>
    void construct(pointer ptr, Args&&... args)
    {
        new(ptr)value_type(std::forward<Args>(args)...);
    }

    // Description:
    // Construct an object of type T1 at the location of ptr, using the value of T1 in the call to the
    // constructor for T1.
    void construct(pointer ptr, const T1& val)
    {
        ::new (reinterpret_cast<void*>(ptr)) T1(val);
    }

    // Description:
    // Call the destructor on the value pointed to by p
    void destroy(pointer p)
    {
        p->T1::~T1();
    }
private:
    MyPool &pool;
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
