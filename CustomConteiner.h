#pragma once
#include <memory>

template<typename _Tp, typename _Alloc>
class CustomContainer_Base
{

};

template <class T, class Alloc = std::allocator<T> >
class CustomContainer : protected CustomContainer_Base<T, Alloc>
{
    Alloc alloc_;

    class node
    {
        T value;
        node *next = nullptr;
        node *previous = nullptr;
    };
    node *first = nullptr;
    node *last = nullptr;
    std::size_t SIZE = 0;

public:
    typedef Alloc allocator_type;
    typedef typename Alloc::value_type value_type;
    typedef typename Alloc::reference reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::difference_type difference_type;
    typedef typename Alloc::size_type size_type;
    typedef typename Alloc::pointer pointer;

    class iterator : public std::iterator<std::input_iterator_tag, value_type>
    {
    public:
        typedef typename Alloc::reference reference;
        typedef typename Alloc::pointer pointer;

        iterator();
        iterator(const iterator& it);
        ~iterator();

        iterator& operator=(const iterator&);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

        iterator& operator++();

        reference operator*() const;
        pointer operator->() const;

    private:
        node* pNode = nullptr;
    };
    class const_iterator : public std::iterator<std::input_iterator_tag, value_type>
    {
    public:
        typedef typename Alloc::const_reference const_reference;
        typedef typename Alloc::const_pointer const_pointer;

        const_iterator ();
        const_iterator (const const_iterator&);
        const_iterator (const iterator&);
        ~const_iterator();

        const_iterator& operator=(const const_iterator&);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

        const_iterator& operator++();

        const_reference operator*() const;
        const_pointer operator->() const;

    private:
        const node *pNode = nullptr;
    };

    CustomContainer();
    CustomContainer(const CustomContainer& cont);
    ~CustomContainer();

    CustomContainer& operator=(const CustomContainer&);
    bool operator==(const CustomContainer&) const;
    bool operator!=(const CustomContainer&) const;

    void push_back(const value_type& value);

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    void swap(CustomContainer&);
    size_type size() const;
    size_type max_size() const;
    bool empty() const;
};
