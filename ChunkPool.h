#pragma once
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
class ChunkPool
{
public:
    using pointer = T*;

    ChunkPool()
    {
        chunk_pool.emplace_back(std::make_unique<Chunk<T, size> >());
    }

    pointer GetNext(std::size_t n)
    {
        assert(n <= size);
        if(chunk_pool.size())
        {
            if(n <= chunk_pool[chunk_pool.size()-1]->getAvailableSpace()+1)
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
        for(auto it = chunk_pool.begin(); it != chunk_pool.end(); ++it)
        {
            if((*it)->isOwned(ptr))
            {
                (*it)->free(ptr, n);
                if((*it)->getAvailableSpace() == size-1)
                    chunk_pool.erase(it);
                break;
            }
        }
    }

private:
    std::vector<std::unique_ptr<Chunk<T, size> > > chunk_pool;
};
//-----------------------------------------------------------------------------------
