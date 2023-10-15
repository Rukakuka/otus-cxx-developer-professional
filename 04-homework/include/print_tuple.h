#include <iostream>
#include <tuple>

namespace custom
{
    // https://habr.com/ru/companies/otus/articles/655715/
    // честно украдено,
    // tuple.begin() еще не изобрели

    template <typename T, std::size_t... I>
    void printTuple__(const T &tp, std::index_sequence<I...>)
    {
        size_t index = 0;
        auto printElem = [&index](const auto &x)
        {
            if (index++ > 0)
                std::cout << ".";
            std::cout << x;
        };

        (printElem(std::get<I>(tp)), ...);
    }

    template <typename T, std::size_t S = std::tuple_size<T>::value>
    void printTuple(const T &tp)
    {
        printTuple__(tp, std::make_index_sequence<S>{});
    }
}
