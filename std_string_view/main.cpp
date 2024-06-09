#include <iostream>
#include <vector> 

#include "string_view.hpp"

void test_string_view() {
    // Creating string views
    bsv::string_view sv0("Hi there!");
    std::cout << sv0 << std::endl;    // Hi there!

    bsv::basic_string_view<char> sv1("Hello, World!");
    bsv::basic_string_view<char> sv2("Hello, C++");
    bsv::basic_string_view<char> sv3("Hello, World!", 5);
    const char* str = "Hello, World!";
    bsv::basic_string_view<char> sv4(str, 5);
    
    // Iterators
    std::cout << "Iterators:\n";
    for (auto it = sv1.begin(); it != sv1.end(); ++it) {
        std::cout << *it;
    }
    std::cout << "\n";
    
    // Element access
    std::cout << "Element access:\n";
    std::cout << sv1[0] << "\n";        // H
    std::cout << sv1.at(1) << "\n";     // e
    std::cout << sv1.front() << "\n";   // H
    std::cout << sv1.back() << "\n";    // !
    std::cout << sv1.data() << "\n";    // Hello, World!
    
    // Capacity
    std::cout << "Capacity:\n";
    std::cout << sv1.size() << "\n";    // 13
    std::cout << sv1.length() << "\n";  // 13
    std::cout << sv1.max_size() << "\n";
    std::cout << std::boolalpha << sv1.empty() << "\n";  // false
    
    // Modifiers
    std::cout << "Modifiers:\n";
    sv1.remove_prefix(7);
    std::cout << sv1 << "\n";           // World!
    sv1.remove_suffix(1);
    std::cout << sv1 << "\n";           // World
    
    bsv::basic_string_view<char> sv6("Hello, World!");
    bsv::basic_string_view<char> sv7("Goodbye, World!");
    sv6.swap(sv7);
    std::cout << sv6 << "\n";           // Goodbye, World!
    std::cout << sv7 << "\n";           // Hello, World!
    
    // Operations
    std::cout << "Operations:\n";
    char buffer[6] = {0};
    sv7.copy(buffer, 5);
    std::cout << buffer << "\n";            // Hello
    
    std::cout << sv7.substr(7, 5) << "\n";  // World
    
    // Comparisons
    std::cout << "Comparisons:\n";
    std::cout << sv7.compare(sv6) << "\n";              // 1

    bsv::basic_string_view<char> sv5("World");
    std::cout << sv7.compare(7, 5, sv5) << "\n";        // 0

    std::cout << sv7.compare(7, 5, sv6, 9, 5) << "\n";  // 0
    
    // Starts/Ends/Contains
    std::cout << "Starts/Ends/Contains:\n";
    std::cout << std::boolalpha << sv7.starts_with("Hello") << "\n";  // false
    std::cout << std::boolalpha << sv7.ends_with("World!") << "\n";   // true
    std::cout << std::boolalpha << sv7.contains("World") << "\n";     // true
    
    // Find
    std::cout << "Find:\n";
    std::cout << sv7.find("World") << "\n";   // 7
    std::cout << sv7.rfind("World") << "\n";  // 7
    std::cout << sv7.find_first_of("lo") << "\n"; // 2
    std::cout << sv7.find_last_of("lo") << "\n";  // 10
    std::cout << sv7.find_first_not_of("Hello") << "\n"; // 5
    std::cout << sv7.find_last_not_of("World!") << "\n"; // 6
}

int main() {
    test_string_view();
    return 0;
}
