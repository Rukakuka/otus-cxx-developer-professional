#include "print_tuple.h"

#include <iostream>
#include <iomanip>
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

namespace custom
{
    namespace impl
    {
        template <typename T>
        struct is_iterable
        {
            template <typename U>
            static decltype(U().begin()) detect(const U &);
            static std::nullptr_t detect(...);
            static constexpr bool value =
                not std::is_same<
                    std::nullptr_t,
                    decltype(detect(std::declval<T>()))>::value;
        };

        template <typename T>
        struct is_tuple : std::false_type
        {
        };

        template <typename... T>
        struct is_tuple<std::tuple<T...>> : std::true_type
        {
        };

        template <class T>
        std::enable_if_t<is_iterable<T>::value> print_ip(const T &container)
        {
            if (!container.empty())
            {
                std::cout << *container.begin();
                std::for_each(std::next(container.begin()), container.end(), [](auto &value)
                              { std::cout << "." << value; });
            }
            std::cout << std::endl;
        }

        template <>
        std::enable_if_t<is_iterable<std::string>::value> print_ip(const std::string &str)
        {
            std::cout << str << std::endl;
        }

        template <class T>
        std::enable_if_t<is_tuple<T>::value> print_ip(const T &tuple)
        {
            custom::printTuple(tuple);
            std::cout << std::endl;
        }

        template <class T>
        std::enable_if_t<std::is_pod<T>::value> print_ip(const T &value)
        {
            size_t s = sizeof(value);
            for (size_t i = s; i > 0; i--)
            {
                std::cout << ((value >> (i - 1) * 8) & 0xFF);
                if (i > 1)
                {
                    std::cout << '.';
                }
            }
            std::cout << std::endl;
        }
    }

    template <typename T>
    void print_ip(const T& v)
    {
        impl::print_ip(v);
    }
}

/**
 * 04-homework
 **/
int main()
{
    try
    {
        std::string s;
        using namespace custom;
        print_ip(int8_t{-1});
        print_ip(int16_t{0});
        print_ip(int32_t{2130706433});
        print_ip(int64_t{8875824491850138409});
        print_ip(std::string("Hello, world!"));
        print_ip(std::vector<int>{100, 200, 300, 400});
        print_ip(std::list<short>{400, 300, 200, 100});
        print_ip(std::make_tuple(123, 456, 789, 0));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
