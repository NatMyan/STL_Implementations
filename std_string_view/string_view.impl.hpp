#include "string_view.hpp"

namespace bsv {
    template <typename CharT, typename Traits>
    constexpr basic_string_view<CharT, Traits>::basic_string_view (const CharT* s, size_type count) 
        : data_(s), size_(count) 
    {}

    
    

} // namespace bsv