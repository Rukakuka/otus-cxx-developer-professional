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
        for (auto __ippart = iter->cbegin(); __ippart != iter->cend(); ++__ippart)
        {
            if (__ippart != iter->cbegin())
            {
                std::printf(".");
            }
            std::printf("%d", *__ippart);
        }
        std::cout << std::endl;
    }

    void print(const std::vector<custom::ip> &pool)
    {
        for (auto __ip = pool.cbegin(); __ip != pool.cend(); ++__ip)
        {
            __print_single_ip(__ip);
        }
    }

    template <typename Compare>
    void print(const std::vector<custom::ip> &pool, Compare comp)
    {
        for (auto __ip = pool.cbegin(); __ip != pool.cend(); ++__ip)
        {
            auto addr = *__ip;
            if (comp(addr))
            {
                __print_single_ip(__ip);
            }
        }
    }
}