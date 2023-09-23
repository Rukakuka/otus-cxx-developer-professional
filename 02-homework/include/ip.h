#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cctype>
#include <iomanip>

namespace custom
{
    class ip
    {
    public:
        ip(std::vector<std::string> &&str)
        {
            std::transform(str.begin(), str.end(), std::back_inserter(address),
                           [](const std::string &str)
                           { return static_cast<uint8_t>(std::stoi(str)); });
        };
        ~ip(){};

        class const_iterator
        {
        private:
            friend class ip;
            std::vector<uint8_t>::const_iterator it;

            explicit const_iterator(std::vector<uint8_t>::const_iterator iter) : it(iter) {}

        public:
            using reference = std::vector<uint8_t>::const_reference;
            using pointer = std::vector<uint8_t>::const_pointer;

            reference operator*() const
            {
                return *it;
            }

            const_iterator &operator++()
            {
                ++it;
                return *this;
            }

            const_iterator operator++(int)
            {
                const_iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const const_iterator &other)
            {
                return it == other.it;
            }

            bool operator!=(const const_iterator &other)
            {
                return !(*this == other);
            }
        };

        const const_iterator cbegin() const
        {
            return const_iterator(address.cbegin());
        }

        const const_iterator cend() const
        {
            return const_iterator(address.cend());
        }

        /********************************************************/

        uint8_t &at(int pos)
        {
            return address.at(pos);
        }

        bool contains(int byte)
        {
            for (auto byte_ = this->cbegin(); byte_ != this->cend(); ++byte_)
            {
                if (*byte_ == byte)
                {
                    return true;
                }
            }
            return false;
        }

        uint32_t as_num()
        {
            return static_cast<uint32_t>(address.at(3) | (address.at(2) << 8) |
                                         (address.at(1) << 16) | (address.at(0) << 24));
        }

    private:
        std::vector<uint8_t> address;
    };
}