#ifndef ALGOS_HPP
#define ALGOS_HPP

#include <iterator>

namespace alg {

    template <typename RandomIt, typename Compare>
    constexpr void push__heap (RandomIt first, RandomIt last, Compare comp);

    template <typename RandomIt, typename Compare>
    constexpr void pop__heap (RandomIt first, RandomIt last, Compare comp);

    template <typename RandomIt, typename Compare>
    constexpr void make__heap (RandomIt first, RandomIt last, Compare comp);

    template <typename RandomIt, typename Compare>
    void heapify (RandomIt first, RandomIt last, RandomIt i, Compare comp);

    template <typename RandomIt>
    RandomIt getChild (RandomIt first, RandomIt last, RandomIt it,
                       typename std::iterator_traits<RandomIt>::difference_type childId); 

} // namespace alg

#include "algos.impl.hpp"

#endif // ALGOS_HPP
