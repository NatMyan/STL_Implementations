#ifndef PQ_IMPL_HPP
#define PQ_IMPL_HPP

namespace pq {
    // ctors-------------------------------------------------------------------------------------------
    /// NOTES: 1. redeclaration may not have default arguments 
    /*         2. std::move is used to indicate that an object t may be "moved from", 
                  i.e. allowing the efficient transfer of resources from t to another object.
                  In particular, std::move produces an xvalue expression that identifies its 
                  argument t. It is exactly equivalent to a static_cast to an rvalue reference type.
    */
    template <typename T, typename Container, typename Compare>
    priority__queue<T, Container, Compare>::priority__queue (const Compare &compare, const Container &cont)
        : c (cont), comp (compare)
    {
        alg::make__heap(c.begin(), c.end(), comp);
    }

    template <typename T, typename Container, typename Compare>
    priority__queue<T, Container, Compare>::priority__queue (const Compare &compare, Container &&cont)
        : c(std::move(cont)), comp (compare)
    {
        alg::make__heap(c.begin(), c.end(), comp);
    }

    template <typename T, typename Container, typename Compare>
    template <typename InputIt>
    priority__queue<T, Container, Compare>::priority__queue (InputIt first, InputIt last, 
                    const Compare &compare, const Container &cont) 
    {
        c.insert(c.end(), first, last);
        alg::make__heap (c.begin(), c.end(), comp);
    }

    template <typename T, typename Container, typename Compare>
    template <typename InputIt>
    priority__queue<T, Container, Compare>::priority__queue(InputIt first, InputIt last, const Compare &compare, Container &&cont)
        : c (std::move(cont)), comp (compare)
    {
        c.insert(c.end(), first, last);
        alg::make__heap(c.begin(), c.end(), comp);
    }
    
    // copy ctors--------------------------------------------------------------------------------------
    template <typename T, typename Container, typename Compare>
    priority__queue<T, Container, Compare>::priority__queue(const priority__queue &other) 
        : c(other.c), comp(other.comp)  
    {}

    template <typename T, typename Container, typename Compare>
    priority__queue<T, Container, Compare>::priority__queue(priority__queue &&other) 
        : c (std::move(other.c)), comp (std::move(other.comp))
    {}

    // = ----------------------------------------------------------------------------------------------
    template <typename T, typename Container, typename Compare>
    auto priority__queue<T, Container, Compare>::operator=(const priority__queue &other) -> priority__queue & {
        if (this != &other) {
            c = other.c;
            comp = other.comp;
        }
        return *this;
    }

    template <typename T, typename Container, typename Compare>
    auto priority__queue<T, Container, Compare>::operator=(priority__queue &&other) -> priority__queue & {
        if (this != &other) {
            c = std::move(other.c);
            comp = std::move(other.comp);
        }
        return *this;
    }

    // funcs-------------------------------------------------------------------------------------------
    template <typename T, typename Container, typename Compare>           
    template <typename... Args>
    void priority__queue<T, Container, Compare>::emplace (Args&&... args) {
        c.emplace_back(std::forward<Args>(args)...); 
        alg::push__heap(c.begin(), c.end(), comp);
    }

    template <typename T, typename Container, typename Compare>
    void priority__queue<T, Container, Compare>::swap (priority__queue& other) 
    noexcept (std::is_nothrow_swappable_v<Container> && std::is_nothrow_swappable_v<Compare>) {
        using std::swap; 
        swap(c, other.c); 
        swap(comp, other.comp);
    }

    template <typename T, typename Container, typename Compare>
    void priority__queue<T, Container, Compare>::pop () {
        alg::pop__heap (c.begin(), c.end(), comp); 
        c.pop_back();
    }

    template <typename T, typename Container, typename Compare>
    void priority__queue<T, Container, Compare>::push (const value_type& value) {  
        c.push_back(value);
        alg::push__heap(c.begin(), c.end(), comp);               
    }

    template <typename T, typename Container, typename Compare>
    void priority__queue<T, Container, Compare>::push (value_type&& value) {  
        c.push_back(std::move(value)); 
        alg::push__heap(c.begin(), c.end(), comp);               
    }

    template <typename T, typename Container, typename Compare>
    template <typename InputIt>    
    void priority__queue<T, Container, Compare>::push_range (InputIt first, InputIt last) {
        for (auto it = first; it != last; ++it) {
            c.push_back(*it);
            alg::push__heap(c.begin(), c.end(), comp);
        }
    }

    template <typename T, typename Container, typename Compare>
    [[nodiscard]] bool priority__queue<T, Container, Compare>::empty () const {
        return c.empty();
    }

    template <typename T, typename Container, typename Compare>
    typename Container::const_reference priority__queue<T, Container, Compare>::top() const {
        return c.front();
    }

    template <typename T, typename Container, typename Compare>
    typename Container::size_type priority__queue<T, Container, Compare>::size() const {
        return c.size();
    }
} // namespace pq

#endif // PQ_IMPL_HPP
