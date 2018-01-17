#pragma once
#include <memory>
#include <algorithm>

template<typename Tp, typename Alloc>
class CustomContainer_Base
{
public:
    struct List_node
    {
        List_node() = default;
        List_node(const Tp& value)
        {
            data = value;
        }

        List_node* next = nullptr;
        List_node* prev = nullptr;

        Tp data;

        Tp* valptr() const { return &data; }
    };
    std::size_t size = 0;

protected:
    using Node_alloc_type = typename Alloc::template
    rebind<List_node>::other;
    Node_alloc_type& get_Node_allocator() noexcept { return M_impl; }
    Node_alloc_type M_impl;
};
//---------------------------------------------------------------------
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

    //------------------------------------------------
    class iterator
    {
    public:
        typedef typename Alloc::reference reference;
        typedef typename Alloc::pointer pointer;

        iterator() = default;
        iterator(Node *node)
        {
            pNode = node;
        }

        iterator(const iterator& it) = default;
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

        reference operator*() const noexcept
        {
            return pNode->data;
        }
        pointer operator->() const noexcept
        {
            return &pNode->data;
        }

        Node* getPointer() const noexcept
        {
            return pNode;
        }

        Node* pNode = nullptr;
    };
    //-------------------------------------------------
    class const_iterator
    {
    public:
        typedef typename Alloc::reference reference;
        typedef typename Alloc::pointer pointer;

        const_iterator () = default;
        const_iterator (const const_iterator&) = default;
        ~const_iterator() = default;

        const_iterator(Node *node)
        {
            pNode = node;
        }

        bool operator==(const iterator& it) const noexcept
        {
            return pNode == it.pNode;
        }
        bool operator!=(const iterator& it) const noexcept
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

        reference operator*() const noexcept
        {
            return pNode->data;
        }

        pointer operator->() const noexcept
        {
            return &pNode->data;
        }

        const Node *pNode = nullptr;
    };
    //------------------------------------------------------
    CustomContainer() = default;
    CustomContainer(const CustomContainer& cont)
    {
        if(*this != cont)
        {
            this->clear();
            std::copy(cont.begin(), cont.end(), std::back_inserter(*this));
        }
    }

    ~CustomContainer()
    {
        this->clear();
    }

    CustomContainer& operator=(const CustomContainer& cont)
    {
        if(*this != cont)
        {
            this->clear();
            std::copy(cont.begin(), cont.end(), std::back_inserter(*this));
        }
        else
        {
            return *this;
        }
    }

    bool operator==(const CustomContainer& cont) const noexcept
    {
        return begin() == cont.begin() && this->size() == cont.size();
    }

    bool operator!=(const CustomContainer& cont) const noexcept
    {
        return begin() != cont.begin() || this->size() != cont.size();
    }

    iterator last()  noexcept
    {
        auto it = this->begin();
        if(it.getPointer())
            while (it.getPointer()->next)
            {
                it++;
            }

        return it;
    }

    void push_back(const value_type& value)
    {
        if(header)
        {
            auto it = last();
            auto node = create_node(value);
            it.getPointer()->next = node;
            node->prev = it.getPointer();
        }
        else
        {
            header = create_node(value);
        }
        setSize(size() + 1);
    }

    iterator begin() noexcept
    {
        return iterator(header);
    }

    iterator rbegin() const noexcept
    {
        return iterator(nullptr);
    }

    const_iterator begin() const noexcept
    {
        return const_iterator(header);
    }
    const_iterator cbegin() const noexcept
    {
        return const_iterator(header);
    }

    iterator end() noexcept { return iterator(nullptr); }
    const_iterator end() const noexcept{ return iterator(nullptr); }
    const_iterator cend() const noexcept { return iterator(nullptr); }

    size_type size() const noexcept
    {
        return CustomContainer_Base<T, Alloc>::size;
    }

    size_type max_size() const noexcept
    {
        return this->get_Node_allocator().max_size();
    }

    bool empty() const noexcept
    {
        return begin() == end();
    }

    void clear()
    {
        auto& alloc = this->get_Node_allocator();
        auto tmp = last();
        for(auto it = tmp; it != this->rbegin();)
        {
            if(it.getPointer()->prev)
            {
                tmp = --it;
                it++;
            }
            else
                tmp = this->rbegin();
            alloc.destroy(it.getPointer());
            alloc.deallocate(it.getPointer(), 1);
            it = tmp;
        }
        header = nullptr;
        setSize(0);
    }

private:
    template<typename... Args>
    Node* create_node(Args&&... args)
    {
        auto& alloc = this->get_Node_allocator();
        auto p = alloc.allocate(1);
        alloc.construct(p, std::forward<Args>(args)...);
        return p;
    }

    void setSize(size_type size) noexcept
    {
        CustomContainer_Base<T, Alloc>::size = size;
    }

    Node* header = nullptr;
};
