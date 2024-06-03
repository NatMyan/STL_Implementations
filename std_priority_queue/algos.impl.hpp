#ifndef ALGOS_IMPL_HPP
#define ALGOS_IMPL_HPP

template <typename RandomIt, typename Compare>
constexpr void alg::make__heap (RandomIt first, RandomIt last, Compare comp) {
    const auto size = std::distance(first, last);
    if (size <= 1) {
        return;
    }
    for (auto i = size / 2; i >= 0; --i) {
        alg::heapify(first, last, std::next(first, i), comp);
    }
}

template <typename RandomIt, typename Compare>
void alg::heapify (RandomIt first, RandomIt last, RandomIt i, Compare comp) {
    auto edge = i;
    if (const auto leftChild = getChild(first, last, i, 1); leftChild != last && comp(*edge,*leftChild)) 
        edge = leftChild;
    if (const auto rightChild = getChild(first, last, i, 2); rightChild != last && comp(*edge,*rightChild)) 
        edge = rightChild;
    
    if (edge != i) {
        using std::swap;
        swap(*edge, *i);
        alg::heapify(first, last, edge, comp);
    }
}

template <typename RandomIt, typename Compare>
constexpr void alg::push__heap (RandomIt first, RandomIt last, Compare comp) {
    const auto elemToPushIter = std::prev(last);
    const auto parentDist = std::distance(first, last);    
    const auto parentIter = std::next(first, (parentDist - 1) / 2 );
    if (first != elemToPushIter && !comp(*elemToPushIter, *parentIter)) {
        using std::swap;
        swap(*parentIter, *elemToPushIter);
        alg::push__heap(first, parentIter + 1, comp);
    }
}

template <typename RandomIt, typename Compare>
constexpr void alg::pop__heap (RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    swap (*first, *std::prev(last)); 
    alg::heapify (first, std::prev(last), first, comp); 
}

template <typename RandomIt>
RandomIt alg::getChild (RandomIt first, RandomIt last, RandomIt it,
                        typename std::iterator_traits<RandomIt>::difference_type childId) {
    const auto index = std::distance(first, it);
    const auto childIndex = 2*index + childId;
    return childIndex >= std::distance(first, last) ? last : std::next(first, childIndex);
}

#endif // ALGOS_IMPL_HPP
