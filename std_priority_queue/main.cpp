#include "pq.hpp"
#include <functional>
#include <iostream>
#include <queue>
#include <string_view>
#include <vector>
 
template <typename T>
void print (std::string_view name, T const& q) {
    std::cout << name << ": \t";
    for (auto const& n : q)
        std::cout << n << ' ';
    std::cout << '\n';
}
 
template <typename Q>
void print_queue (std::string_view name, Q q) {
    // NB: q is passed by value because there is no way to traverse
    // priority_queue's content without erasing the queue.
    for (std::cout << name << ": \t"; !q.empty(); q.pop())
        std::cout << q.top() << ' ';
    std::cout << '\n';
}
 
int main() {
    const auto data = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
    print("data", data);
 
    pq::priority__queue<int> q1; // Min priority queue
    for (int n : data)
        q1.push(n); 
    print_queue("q1", q1);
 
    // std::less<int> makes the min priority queue act as a max priority queue
    pq::priority__queue<int, std::vector<int>, std::less<int>>
        maxq2 (data.begin(), data.end()); 
    print_queue("maxq2", maxq2);
 
    // Second way to define a max priority queue
    pq::priority__queue maxq3 (data.begin(), data.end(), std::less<int>()); 
    print_queue("maxq3", maxq3);
 
    // Using a custom function object to compare elements.
    struct {
        bool operator() (const int l, const int r) const { return l > r; }
    } customGreater;
    pq::priority__queue q4 (data.begin(), data.end(), customGreater); 
    print_queue("q4", q4);
 
    // Using lambda to compare elements.
    auto cmp = [](int left, int right) { return (left ^ 1) > (right ^ 1); };
    pq::priority__queue<int, std::vector<int>, decltype(cmp)> q5(cmp); 
    for (int n : data)
        q5.push(n); 
    print_queue("q5", q5);
}