#pragma once 

#include <iostream>
#include <stdio.h>

namespace custom
{
    class Logger
    {
    public:
        static void Error(const std::string &m)
        {
            std::cout << "[ERROR  ] " << m << std::endl;
        }

        static void Info(const std::string &m)
        {
            std::cout << "[INFO   ] " << m << std::endl;
        }

        static void Warning(const std::string &m)
        {
            std::cout << "[WARNING] " << m << std::endl;
        }
    };
}
