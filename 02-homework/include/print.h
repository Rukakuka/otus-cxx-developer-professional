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

#include "ip.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
namespace custom
{
    std::vector<std::string> split(const std::string &str, char d)
    {
        std::vector<std::string> r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while (stop != std::string::npos)
        {
            r.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }

        r.push_back(str.substr(start));

        return r;
    }

    void __print_single_ip(const std::vector<ip>::const_iterator &iter)
    {
        for (auto ip_part = iter->cbegin(); ip_part != iter->cend(); ++ip_part)
        {
            if (ip_part != iter->cbegin())
            {
                std::printf(".");
            }
            std::printf("%d", *ip_part);
        }
        std::cout << std::endl;
    }

    void print(const std::vector<custom::ip> &pool)
    {
        for (auto ip_ = pool.cbegin(); ip_ != pool.cend(); ++ip_)
        {
            __print_single_ip(ip_);
        }
    }

    template <typename Compare>
    void print(const std::vector<custom::ip> &pool, Compare comp)
    {
        for (auto ip_ = pool.cbegin(); ip_ != pool.cend(); ++ip_)
        {
            auto addr = *ip_;
            if (comp(addr))
            {
                __print_single_ip(ip_);
            }
        }
    }
}