#include "CustomConteiner.h"

template <class T, class Alloc>
CustomContainer<T, Alloc>::iterator::iterator()
{
}

template <class T, class Alloc>
CustomContainer<T, Alloc>::iterator::iterator(const CustomContainer::iterator &it)
{
    pNode = it.pNode;
}

template <class T, class Alloc>
CustomContainer<T, Alloc>::iterator::~iterator()
{
}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::iterator&
CustomContainer<T, Alloc>::iterator::operator=(const CustomContainer<T, Alloc>::iterator &it)
{
    if(pNode != it.pNode)
        pNode = it.pNode;
    return this;
}

template <class T, class Alloc>
bool CustomContainer<T, Alloc>::iterator::operator==(const CustomContainer::iterator &it) const
{
    return pNode == it.pNode;
}

template <class T, class Alloc>
bool CustomContainer<T, Alloc>::iterator::operator!=(const CustomContainer::iterator &it) const
{
    return pNode != it.pNode;
}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::iterator&
CustomContainer<T, Alloc>::iterator::operator++()
{
    pNode = pNode->next;
    return pNode;
}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::iterator::reference
CustomContainer<T, Alloc>::iterator::operator*() const
{
    return pNode->value;
}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::iterator::pointer
CustomContainer<T, Alloc>::iterator::operator->() const
{
    return &pNode->value;
}


template <class T, class Alloc>
CustomContainer<T, Alloc>::const_iterator::const_iterator()
{
}

template <class T, class Alloc>
CustomContainer<T, Alloc>::const_iterator::const_iterator(const CustomContainer<T, Alloc>::const_iterator &it)
{
    pNode = it.pNode;
}

template <class T, class Alloc>
CustomContainer<T, Alloc>::const_iterator::const_iterator(const CustomContainer<T, Alloc>::iterator &it)
{
    pNode = it.pNode;
}

template <class T, class Alloc>
CustomContainer<T, Alloc>::const_iterator::~const_iterator()
{
}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::const_iterator&
CustomContainer<T, Alloc>::const_iterator::operator=(const CustomContainer<T, Alloc>::const_iterator &it)
{
    if(pNode != it.pNode)
        pNode = it.pNode;
    return this;
}

template <class T, class Alloc>
bool CustomContainer<T, Alloc>::const_iterator::operator==(const CustomContainer<T, Alloc>::const_iterator &it) const
{
    return pNode == it.pNode;
}

template <class T, class Alloc>
bool CustomContainer<T, Alloc>::const_iterator::operator!=(const CustomContainer<T, Alloc>::const_iterator &it) const
{
    return pNode != it.pNode;
}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::const_iterator &CustomContainer<T, Alloc>::const_iterator::operator++()
{
    pNode = pNode->next;
    return pNode;
}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::const_reference
CustomContainer<T, Alloc>::const_iterator::operator*() const
{
    return pNode->value;
}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::const_iterator::const_pointer
CustomContainer<T, Alloc>::const_iterator::operator->() const
{
    return &pNode->value;
}

template <class T, class Alloc>
CustomContainer<T, Alloc>::CustomContainer()
{
}

template <class T, class Alloc>
CustomContainer<T, Alloc>::CustomContainer(const CustomContainer &cont)
{
    if(*this != cont)
    {
        this->~CustomContainer();
        for(auto it = cont.begin(); it != cont.end(); ++it)
        {
//            auto ptr =
        }
    }
}

template <class T, class Alloc>
CustomContainer<T, Alloc>::~CustomContainer()
{

}

template <class T, class Alloc>
CustomContainer<T, Alloc> &CustomContainer<T, Alloc>::operator=(const CustomContainer &)
{

}

template <class T, class Alloc>
bool CustomContainer<T, Alloc>::operator==(const CustomContainer<T, Alloc> &) const
{

}

template <class T, class Alloc>
bool CustomContainer<T, Alloc>::operator!=(const CustomContainer<T, Alloc> &) const
{

}

template <class T, class Alloc>
void CustomContainer<T, Alloc>::push_back(const CustomContainer<T, Alloc>::value_type &value)
{
    auto ptr = alloc_.allocate(1);
    alloc_.construct(ptr, value);
}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::iterator
CustomContainer<T, Alloc>::begin()
{

}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::const_iterator
CustomContainer<T, Alloc>::begin() const
{

}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::const_iterator
CustomContainer<T, Alloc>::cbegin() const
{

}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::iterator
CustomContainer<T, Alloc>::end()
{

}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::const_iterator
CustomContainer<T, Alloc>::end() const
{

}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::const_iterator
CustomContainer<T, Alloc>::cend() const
{

}

template <class T, class Alloc>
void CustomContainer<T, Alloc>::swap(CustomContainer<T, Alloc> &)
{

}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::size_type
CustomContainer<T, Alloc>::size() const
{

}

template <class T, class Alloc>
typename CustomContainer<T, Alloc>::size_type
CustomContainer<T, Alloc>::max_size() const
{

}

template <class T, class Alloc>
bool CustomContainer<T, Alloc>::empty() const
{

}
