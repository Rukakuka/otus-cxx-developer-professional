#pragma once

#include <string>
#include <stdexcept>
#include <cstring>
#include <memory>

#include "log.h"

namespace custom
{
    /**
     * Definetely not thread-safe
     */
    template <class T>
    class pool_allocator : std::allocator_traits<std::allocator<T>>
    {
    public:
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        pool_allocator() noexcept {}
        ~pool_allocator()
        {
            custom::log("Destroying, total number of new[] is %d, total number of delete[] is %d\n",
                        alloc, dealloc);
        }

        template <class U>
        pool_allocator(const pool_allocator<U> &) noexcept
        {
        }

        T *allocate(std::size_t n)
        {
            custom::log("%s", "Allocator called\n");
            std::size_t req_sz = n * sizeof(T);
            int cur;
            custom::log("Requested %ld items of size %ld with total size %ld\n",
                        n, sizeof(T), req_sz);
            if (pos + req_sz > size)
            {
                custom::log("Can't fetch %ld bytes from pool, %ld bytes left\n",
                            req_sz, (size - pos));
                if (expand(req_sz))
                {
                    cur = 0;
                    pos = req_sz;
                    custom::log("Expaned new pool is %ld bytes at %p\n", size,
                                reinterpret_cast<T *>(reinterpret_cast<char *>(pool_start) + cur));
                }
                else
                {
                    throw std::bad_alloc();
                }
            }
            else
            {
                custom::log("Fetching %ld bytes from pool, %ld more bytes left\n",
                            req_sz, (size - pos));
                cur = pos;
                pos += req_sz;
                custom::log("Object placed at %p, pos is %ld \n",
                            reinterpret_cast<T *>(reinterpret_cast<char *>(pool_start) + cur), pos);
            }
            return reinterpret_cast<T *>(reinterpret_cast<char *>(pool_start) + cur);
        }

        void deallocate(T *p, [[maybe_unused]] std::size_t n)
        {
            custom::log("Request deallocating %ld bytes at %p\n",
                        n * sizeof(T), reinterpret_cast<char *>(p));

            if (reinterpret_cast<char *>(p) > reinterpret_cast<char *>(pool_start) &&
                reinterpret_cast<char *>(p) <= reinterpret_cast<char *>(pool_start + size))
            {
                custom::log("Data is inside the pool, skip dealloc\n", reinterpret_cast<char *>(p));
            }
            else if (reinterpret_cast<char *>(p) == reinterpret_cast<char *>(pool_start))
            {
                custom::log("Deallocated %ld bytes at origin %p\n", size, pool_start);
                delete[] pool_start;
                dealloc++;
            }
            else
            {
                dealloc_old_pools(reinterpret_cast<char *>(p));
            }
        }

        template <class Up, class... Args>
        void construct(Up *p, Args &&...args)
        {
            custom::log("Container constructed object at %p\n", p);
            ::new (reinterpret_cast<void *>(p)) Up(std::forward<Args>(args)...);
            pos += sizeof(T);
        }

        void destroy(pointer p)
        {
            p->~T();
        }

        template <class U>
        struct rebind
        {
            typedef pool_allocator<U> other;
        };

    private:
        static int pos;
        static std::size_t size;
        static char *pool_start;
        static int chunk_cnt;
        struct Chunk
        {
            char *pool_start;
            Chunk *next;
            size_t size;
        };
        static struct Chunk chunks[100];
        static int alloc;
        static int dealloc;

        size_t expand(std::size_t n)
        {
            size_t sz = (2 * size > n) ? (2 * size) : (2 * n);
            char *new_pool = new char[sz];
            alloc++;
            if (new_pool)
            {
                custom::log("Found new free block of size %ld at %p\n", sz, new_pool);
                if (pool_start)
                {
                    if (chunk_cnt < 100)
                    {
                        save_old_pool();
                    }
                    else
                    {
                        throw std::bad_alloc();
                    }
                }
                pool_start = new_pool;
                size = sz;
                return sz;
            }
            else
            {
                throw std::bad_alloc();
            }
        };

        void dealloc_old_pools(char *req_addr)
        {
            for (Chunk *c = &chunks[0]; c != nullptr; c = c->next)
            {
                if (reinterpret_cast<char *>(req_addr) == reinterpret_cast<char *>(c->pool_start))
                {
                    custom::log("Deallocated %ld bytes of previous pool%d at %p\n",
                                c->size, chunk_cnt - 1, c->pool_start);
                    delete[] c->pool_start;
                    dealloc++;
                    if (chunk_cnt > 0)
                    {
                        chunks[chunk_cnt - 1].next = nullptr;
                    }
                    chunk_cnt--;
                }
            }
        }

        void save_old_pool()
        {
            custom::log("Saved previous pool at %p\n", pool_start);
            chunks[chunk_cnt].pool_start = pool_start;
            chunks[chunk_cnt].next = nullptr;
            chunks[chunk_cnt].size = size;
            if (chunk_cnt > 0)
            {
                chunks[chunk_cnt - 1].next = &chunks[chunk_cnt];
            }
            chunk_cnt++;
        }
    };

    template <class T, class U>
    constexpr bool operator==(const custom::pool_allocator<T> &a1,
                              const custom::pool_allocator<U> &a2) noexcept
    {
        return true;
    }

    template <class T, class U>
    constexpr bool operator!=(const custom::pool_allocator<T> &a1,
                              const custom::pool_allocator<U> &a2) noexcept
    {
        return false;
    }
} // namespace custom