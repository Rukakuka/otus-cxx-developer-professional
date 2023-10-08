#pragma once

#include <iostream>
#include <cstdio>

namespace custom
{
    template <typename... Args>
    [[maybe_unused]]static void log([[maybe_unused]]const char *fmt, [[maybe_unused]]Args... args)
    {
#ifndef NDEBUG
        std::printf(fmt, args...);
#endif
    }

    [[maybe_unused]]static void dump_memory(char *from, unsigned long length)
    {
        custom::log("%s", "-------------------------\n");
        unsigned long j = 0;
        for (char *i = from; j < length; i++)
        {
            custom::log("| %p | 0x%2X |\n", i, *reinterpret_cast<char *>(i));
            j++;
        }
        custom::log("%s", "-------------------------\n");
    }
}