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
        struct prio4
        {
        };
        struct prio3 : public prio4
        {
        };
        struct prio2 : public prio3
        {
        };
        struct prio1 : public prio2
        {
        };

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

        template <class T, class = std::enable_if_t<is_iterable<T>::value>>
        void print_ip(T &container, prio1)
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
        void print_ip(std::string &str, prio1)
        {
            std::cout << str << std::endl;
        }

        template <class T, class = std::enable_if_t<is_tuple<T>::value>>
        void print_ip(T &tuple, prio2)
        {
            custom::printTuple(tuple);
            std::cout << std::endl;
        }

        template <class T, class = std::enable_if_t<std::is_pod<T>::value>>
        void print_ip(T &value, prio3)
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

        template <>
        void print_ip(const char *&str, prio3)
        {
            std::cout << str << std::endl;
        }

        template <typename T>
        void print_ip(T &value, prio4)
        {
            std::cout << value << std::endl;
        }

    }

    template <typename T>
    void print_ip(T v)
    {
        impl::print_ip(v, impl::prio1{});
    }

}

int main(int argc, char const *argv[])
{

    (void)argc;
    (void)argv;

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

        // custom::print_ip("Hello, world!");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
