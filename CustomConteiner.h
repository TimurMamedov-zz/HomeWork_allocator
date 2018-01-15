#pragma once
#include <memory>

template<typename Tp, typename Alloc>
class CustomContainer_Base
{
public:
    template<Tp>
    struct List_node
    {
        List_node* next;
        List_node* prev;

        std::size_t size;

        Tp data;

        Tp* valptr() { return &data; }
    };

protected:
    using Node_alloc_type = typename Alloc::template
    rebind<List_node>::other;
    Node_alloc_type& get_Node_allocator(){ return M_impl; }
    Node_alloc_type M_impl;
};

template <class T, class Alloc = std::allocator<T> >
class CustomContainer : protected CustomContainer_Base<T, Alloc>
{
public:
    typedef Alloc allocator_type;
    typedef typename Alloc::value_type value_type;
    typedef typename Alloc::reference reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::difference_type difference_type;
    typedef typename Alloc::size_type size_type;
    typedef typename Alloc::pointer pointer;

    typedef typename CustomContainer_Base<T, Alloc>::List_node Node;

    class iterator : public std::iterator<std::input_iterator_tag, value_type>
    {
    public:
        typedef typename Alloc::reference reference;
        typedef typename Alloc::pointer pointer;

        iterator() = default;
        iterator(const iterator& it) = delete;
        ~iterator() = default;

        bool operator==(const iterator& it) const
        {
            return pNode == it.pNode;
        }
        bool operator!=(const iterator& it) const
        {
            return pNode != it.pNode;
        }

        iterator& operator++() noexcept
        {
            pNode = pNode->next;
            return *this;
        }

        iterator operator++(int) noexcept
        {
            auto tmp = *this;
            pNode = pNode->next;
            return tmp;
        }

        iterator& operator--() noexcept
        {
            pNode = pNode->prev;
            return *this;
        }

        iterator operator--(int) noexcept
        {
            auto tmp = *this;
            pNode = pNode->prev;
            return tmp;
        }

        reference operator*() const
        {
            return pNode->data;
        }
        pointer operator->() const
        {
            return &pNode->data;
        }

        Node* pNode = nullptr;
    };
    class const_iterator : public std::iterator<std::input_iterator_tag, value_type>
    {
    public:
        typedef typename Alloc::const_reference const_reference;
        typedef typename Alloc::const_pointer const_pointer;

        const_iterator () = default;
        const_iterator (const const_iterator&) = delete;
        const_iterator (const iterator&) = delete;
        ~const_iterator() = default;

        bool operator==(const const_iterator& it) const
        {

        }
        bool operator!=(const const_iterator& it) const
        {

        }

        const_iterator& operator++()
        {

        }

        const_reference operator*() const
        {

        }

        const_pointer operator->() const
        {

        }

        const Node *pNode = nullptr;
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

private:
    template<typename... Args>
    Node* create_node(Args&&... args)
    {
        auto& alloc = this->get_Node_allocator();
        auto p = alloc.allocate(1);
        alloc.construct(p, std::forward<Args>(args)...);
        return p;
    }
};
