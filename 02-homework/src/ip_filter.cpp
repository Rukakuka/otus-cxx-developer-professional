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
#include "print.h"

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    try
    {
        std::vector<custom::ip> pool;
        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = custom::split(line, '\t');
            auto ip = custom::ip(std::move(custom::split(v.at(0), '.')));
            pool.emplace_back(ip);
        }

        // reverse lexicographically sort
        std::sort(pool.begin(), pool.end(), [](custom::ip &first, custom::ip &second)
                  { return first.as_num() > second.as_num(); });

        print(pool);

        print(pool, [](custom::ip &ip_)
              { return ip_.at(0) == 1; });

        print(pool, [](custom::ip &ip_)
              { return ip_.at(0) == 46 && ip_.at(1) == 70; });

        print(pool, [](custom::ip &ip_)
              { return ip_.contains(46); });
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
