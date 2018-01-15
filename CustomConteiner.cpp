#include "CustomConteiner.h"

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
