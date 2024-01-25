// Natalie Manukyan

/* 
Implement priority queue based on min-heap data structure, satisifying 
the synatactic and semantic requirements of std::priority_queue adapter.
*/
 
/// NOTE: I'm trying to mimic the style of the STL...

#ifndef PQ_HPP
#define PQ_HPP

#include "algos.hpp"
#include <vector>

namespace pq {
    template <typename T, typename Container = std::vector<T>,
              typename Compare = std::greater<typename Container::value_type>>
    class priority__queue {
        private:
            Container c;
            Compare comp;

        public:
            using container_type = Container;
            using value_compare	= Compare;
            using value_type = typename Container::value_type;  
            using size_type = typename Container::size_type;
            using reference = typename Container::reference;
            using const_reference = typename Container::const_reference;            
            
        public:
            explicit priority__queue(const Compare &compare = Compare(), const Container &cont = Container());
            priority__queue(const Compare &compare, Container &&cont);

            template <typename InputIt>
            priority__queue(InputIt first, InputIt last, const Compare &compare = Compare(), 
                            const Container &cont = Container());
            template <typename InputIt>
            priority__queue(InputIt first, InputIt last, const Compare &compare, Container &&cont);

            ~priority__queue() =default;

            priority__queue(const priority__queue &other);
            priority__queue(priority__queue &&other);

            priority__queue &operator=(const priority__queue &other);
            priority__queue &operator=(priority__queue &&other);

        public:
            [[nodiscard]] bool empty() const;  
            size_type size() const;
            const_reference top() const;           

        public:
            template <typename... Args>           
            void emplace (Args&&... args);

            template <typename InputIt>
            void push_range (InputIt first, InputIt last);

            void push (const value_type& value);     
            void push (value_type&& value);                  
            void pop ();                            

            void swap (priority__queue& other) noexcept (std::is_nothrow_swappable_v<Container> &&
                                                         std::is_nothrow_swappable_v<Compare>);               
    };

    template <typename Comp, typename Container>
    priority__queue (Comp, Container) 
    -> priority__queue<typename Container::value_type, Container, Comp>;

    template <typename InputIt, 
              typename Comp = std::greater<typename std::iterator_traits<InputIt>::value_type>,
              typename Container = std::vector<typename std::iterator_traits<InputIt>::value_type>>
    priority__queue(InputIt, InputIt, Comp = Comp(), Container = Container())
    -> priority__queue<typename std::iterator_traits<InputIt>::value_type, Container, Comp>;

} // namespace pq

#include "pq.impl.hpp"

#endif // PQ_HPP

/*
Methods                       Time Complexity      Auxiliary Space
priority_queue::empty()       O(1)                 O(1)
priority_queue::size()        O(1)                 O(1)
priority_queue::top()         O(1)                 O(1)
priority_queue::push()        O(logN)              O(1)
priority_queue::push_range()  ? O(nlogN)           ? O(1)
priority_queue::pop()         O(logN)              O(1)
priority_queue::swap()        O(1)                 O(N)
priority_queue::emplace()     O(logN)              O(1)
priority_queue value_type     O(1)                 O(1)
*/
