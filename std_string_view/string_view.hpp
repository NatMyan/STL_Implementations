#ifndef STRING_VIEW_HPP
#define STRING_VIEW_HPP

#include <iterator>
#include <string>

namespace bsv {
    template <typename CharT, typename Traits = std::char_traits<CharT> > 
    class basic_string_view {
        private:
            const_pointer ptr_;
            size_type size_;

        public:
            using traits_type = Traits;
            using value_type = CharT;
            using pointer = CharT*;
            using const_pointer = const CharT*;
            using reference = CharT&;
            using const_reference = const CharT&;
            using const_iterator = std::countiguous_iterator;
            using iterator = const_iterator;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;
            using reverse_iterator = const_reverse_iterator;
            using size_type = std::size_t;
            using difference_type = std::ptrdiff_t;

        public: 
            constexpr basic_string_view() noexcept;
            constexpr basic_string_view (const basic_string_view& other) noexcept = default;
            constexpr basic_string_view (const CharT* s, size_type count);
            constexpr basic_string_view (const CharT* s);
            
            template <class It, class End>
            constexpr basic_string_view (It first, End last);
                
            template <class R> 
            constexpr explicit basic_string_view (R&& r);

            constexpr basic_string_view (std::nullptr_t) = delete;

            constexpr basic_string_view& operator= (const basic_string_view& view) noexcept = default;

        public: // Iterators
            constexpr const_iterator begin() const noexcept;
            constexpr const_iterator cbegin() const noexcept;

            constexpr const_iterator end() const noexcept;
            constexpr const_iterator cend() const noexcept;

            constexpr const_reverse_iterator rbegin() const noexcept;
            constexpr const_reverse_iterator crbegin() const noexcept;

            constexpr const_reverse_iterator rend() const noexcept;
            constexpr const_reverse_iterator crend() const noexcept;
        
        public: // Element access 
            constexpr const_reference operator[] (size_type pos) const;
            constexpr const_reference at (size_type pos) const;
            constexpr const_reference front() const;
            constexpr const_reference back() const;
            constexpr const_pointer data() const noexcept;

        public: // Capacity
            constexpr size_type size() const noexcept;
            constexpr size_type length() const noexcept;
            constexpr size_type max_size() const noexcept;
            [[nodiscard]] constexpr bool empty() const noexcept;

        public: // Modifiers
            constexpr void remove_prefix (size_type n);
            constexpr void remove_suffix (size_type n);
            constexpr void swap (basic_string_view& v) noexcept;

        public: // Operations
            constexpr size_type copy (CharT* dest, size_type count, size_type pos = 0) const;
            constexpr basic_string_view substr (size_type pos = 0, size_type count = npos) const;

            constexpr int compare (basic_string_view v) const noexcept;
            constexpr int compare (size_type pos1, size_type count1, basic_string_view v) const;
            constexpr int compare (size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2) const;
            constexpr int compare (const CharT* s) const;
            constexpr int compare (size_type pos1, size_type count1, const CharT* s) const;
            constexpr int compare (size_type pos1, size_type count1, const CharT* s, size_type count2) const;

            constexpr bool starts_with (basic_string_view sv) const noexcept;
            constexpr bool starts_with (CharT ch) const noexcept;
            constexpr bool starts_with (const CharT* s) const;

            constexpr bool ends_with (basic_string_view sv) const noexcept;
            constexpr bool ends_with (CharT ch) const noexcept;
            constexpr bool ends_with (const CharT* s) const;

            constexpr bool contains (basic_string_view sv) const noexcept;
            constexpr bool contains (CharT c) const noexcept;
            constexpr bool contains (const CharT* s) const;
            
            constexpr size_type find (basic_string_view v, size_type pos = 0) const noexcept;
            constexpr size_type find (CharT ch, size_type pos = 0) const noexcept;
            constexpr size_type find (const CharT* s, size_type pos, size_type count) const;
            constexpr size_type find (const CharT* s, size_type pos = 0) const;
            
            constexpr size_type rfind (basic_string_view v, size_type pos = npos) const noexcept;
            constexpr size_type rfind (CharT ch, size_type pos = npos) const noexcept;
            constexpr size_type rfind (const CharT* s, size_type pos, size_type count) const;
            constexpr size_type rfind (const CharT* s, size_type pos = npos) const;
            
            constexpr size_type find_first_of (basic_string_view v, size_type pos = 0) const noexcept;
            constexpr size_type find_first_of (CharT ch, size_type pos = 0) const noexcept;
            constexpr size_type find_first_of (const CharT* s, size_type pos, size_type count) const;
            constexpr size_type find_first_of (const CharT* s, size_type pos = 0) const;
            
            constexpr size_type find_last_of (basic_string_view v, size_type pos = npos) const noexcept;
            constexpr size_type find_last_of (CharT ch, size_type pos = npos) const noexcept;
            constexpr size_type find_last_of (const CharT* s, size_type pos, size_type count) const;
            constexpr size_type find_last_of (const CharT* s, size_type pos = npos) const;
            
            constexpr size_type find_first_not_of (basic_string_view v, size_type pos = 0) const noexcept;
            constexpr size_type find_first_not_of (CharT ch, size_type pos = 0) const noexcept;
            constexpr size_type find_first_not_of (const CharT* s, size_type pos, size_type count) const;
            constexpr size_type find_first_not_of (const CharT* s, size_type pos = 0) const;
            
            constexpr size_type find_last_not_of (basic_string_view v, size_type pos = npos) const noexcept;
            constexpr size_type find_last_not_of (CharT ch, size_type pos = npos) const noexcept;
            constexpr size_type find_last_not_of (const CharT* s, size_type pos, size_type count) const;
            constexpr size_type find_last_not_of (const CharT* s, size_type pos = npos) const;
    };
} // namespace bsv

#endif // STRING_VIEW_HPP