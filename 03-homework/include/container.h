#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <memory>

#include "log.h"

namespace custom
{

    template <typename T, typename Alloc = std::allocator<T>>
    class container
    {
    public:
        container() {}
        ~container() {}

        void emplace_back([[maybe_unused]] const T &elem)
        {
            if (size_ == capacity)
            {
                capacity = capacity * 2 + 1;
                T *newData = alloc.allocate(capacity);
                std::copy(begin(), end(), newData);
                std::swap(data, newData);
                alloc.deallocate(newData, capacity);
            }

            alloc.construct(&data[size_], elem);
            ++size_;
        }

        T operator[](unsigned long i)
        {
            if (i < size_)
            {
                return data[i];
            }
            else
            {
                throw std::out_of_range("custom::container::operator[](int i) out of range");
            }
        };

        size_t size()
        {
            return size_;
        }

    private:
        Alloc alloc;
        T *data = nullptr;
        size_t capacity = 0;
        size_t size_ = 0;

    public:
        class container_iterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;

            container_iterator(pointer ptr) : m_ptr(ptr) {}
            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }
            container_iterator &operator++()
            {
                m_ptr++;
                return *this;
            }
            container_iterator operator++(int)
            {
                container_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator==(const container_iterator &other)
            {
                return m_ptr == other.m_ptr;
            };
            bool operator!=(const container_iterator &other)
            {
                return m_ptr != other.m_ptr;
            };

        private:
            pointer m_ptr;
        };

        container_iterator begin()
        {
            return container_iterator(&data[0]);
        }
        container_iterator end()
        {
            return container_iterator(&data[size_]);
        }
    };



} // namespace custom