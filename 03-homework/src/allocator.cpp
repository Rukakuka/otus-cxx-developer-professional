#include <iostream>
#include <map>
#include <functional>

#include "allocator.h"
#include "container.h"

namespace custom
{
    template <typename T>
    char *pool_allocator<T>::pool_start = new char[10];

    template <typename T>
    int pool_allocator<T>::pos = 0;

    template <typename T>
    std::size_t pool_allocator<T>::size = 10;

    template <typename T>
    int pool_allocator<T>::chunk_cnt = 0;

    template <typename T>
    typename pool_allocator<T>::Chunk pool_allocator<T>::chunks[100];

    template <typename T>
    int pool_allocator<T>::alloc = 0;

    template <typename T>
    int pool_allocator<T>::dealloc = 0;
}

template <typename T, typename U, typename less, typename alloc>
void print_map(const std::map<T, U, less, alloc> &map)
{
    for (auto const &[key, val] : map)
    {
        std::cout << key << ' ' << val << std::endl;
    }
}

template <typename T, typename alloc>
void print_custom_container(custom::container<T, alloc> &container)
{
    for (auto &elem : container)
    {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

int factorial(int n)
{
    return n > 1 ? n * factorial(n - 1) : 1;
}

/**
 * 03-homework
 **/
int main(int argc, char const *argv[])
{

    (void)argc;
    (void)argv;

    try
    {
        /**
         * - создание экземпляра std::map<int, int>
         * - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
         */
        auto map_std_alloc = std::map<int, int>();
        for (int i = 0; i < 10; i++)
        {
            map_std_alloc.insert({i, factorial(i)});
        };
        print_map(map_std_alloc);

        /**
         * - создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
         * - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
         * - вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
         */
        auto map_custom_alloc = std::map<int, int, std::less<int>, custom::pool_allocator<std::map<int, int>>>();
        for (int i = 0; i < 10; i++)
        {
            map_custom_alloc.insert({i, factorial(i)});
        };
        print_map<int, int>(map_custom_alloc);

        /**
         * - создание экземпляра своего контейнера для хранения значений типа int
         * - заполнение 10 элементами от 0 до 9
         */
        auto custom_container_std_alloc = custom::container<int>();
        for (int i = 0; i < 10; i++)
        {
            custom_container_std_alloc.emplace_back(i);
        };
        print_custom_container(custom_container_std_alloc);

        /**
         * - создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором, ограниченным 10 элементами
         * - заполнение 10 элементами от 0 до 9
         * - вывод на экран всех значений, хранящихся в контейнере
         */
        auto custom_container_custom_alloc = custom::container<int, custom::pool_allocator<int>>();
        for (int i = 0; i < 10; i++)
        {
            custom_container_custom_alloc.emplace_back(i);
        };
        print_custom_container(custom_container_custom_alloc);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
