#ifndef STRING_VIEW_HPP
#define STRING_VIEW_HPP

#include <iterator>
#include <string>

namespace bsv {
    template <typename CharT, typename Traits = std::char_traits<CharT> > 
    class basic_string_view {
        public:
            static constexpr size_type npos = size_type(-1);

        public:
            using traits_type = Traits;
            using value_type = CharT;
            using pointer = CharT*;
            using const_pointer = const CharT*;
            using reference = CharT&;
            using const_reference = const CharT&;
            using const_iterator = const CharT*; // std::countiguous_iterator;
            using iterator = const_iterator;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;
            using reverse_iterator = const_reverse_iterator;
            using size_type = std::size_t;
            using difference_type = std::ptrdiff_t;

        private:
            const_pointer data_;
            size_type size_;

        public: 
            // Default constructor. Constructs an empty std::basic_string_view. After construction, data() is equal to nullptr, 
            // and size() is equal to ​0​.
            constexpr basic_string_view() noexcept : data_(nullptr), size_(0) {};

            // Copy constructor. Constructs a view of the same content as other. After construction, data() is equal to other.data(), 
            // and size() is equal to other.size().
            constexpr basic_string_view (const basic_string_view& other) noexcept = default;

            // Constructs a view of the first count characters of the character array starting with the element pointed by s. 
            // s can contain null characters. The behavior is undefined if [s, s + count) is not a valid range (even though the 
            // constructor may not access any of the elements of this range). After construction, data() is equal to s, and size() 
            // is equal to count.
            constexpr basic_string_view (const CharT* s, size_type count) : data_(s), size_(count) {}

            // Constructs a view of the null-terminated character string pointed to by s, not including the terminating null character. 
            // The length of the view is determined as if by Traits::length(s). The behavior is undefined if [s, s + Traits::length(s)) 
            // is not a valid range. After construction, data() is equal to s, and size() is equal to Traits::length(s).
            constexpr basic_string_view (const CharT* s) : data_(s), size_(Traits::length(s)) {}
            
            // Constructs a std::basic_string_view over the range [first, last). The behavior is undefined if [first, last) is not a 
            // valid range, if It does not actually model contiguous_iterator, or if End does not actually model sized_sentinel_for 
            // for It. After construction, data() is equal to std::to_address(first), and size() is equal to last - first.
            // This overload participates in overload resolution only if 
            //         It satisfies contiguous_iterator,
            //         End satisfies sized_sentinel_for for It,
            //         std::iter_value_t<It> and CharT are the same type, and
            //         End is not convertible to std::size_t.
            template <class It, class End>
            constexpr basic_string_view (It first, End last) : data_(std::to_adress(first)), size_(std::distance(first, last)) {
                static_assert(std::is_same_v<std::iter_value_t<It>, CharT>, "Iterator value type must be the same as CharT");
                static_assert(std::contiguous_iterator<It>, "It must satisfy contiguous_iterator");
                static_assert(std::sized_sentinel_for<End, It>, "End must satisfy sized_sentinel_for<It>");
            }
            
            // Constructs a std::basic_string_view over the range r. After construction, data() is equal to ranges::data(r), 
            // and size() is equal to ranges::size(r).
            // This overload participates in overload resolution only if
            //         std::remove_cvref_t<R> is not the same type as std::basic_string_view,
            //         R models contiguous_range and sized_range,
            //         ranges::range_value_t<R> and CharT are the same type,
            //         R is not convertible to const CharT*, and
            //         Let d be an lvalue of type std::remove_cvref_t<R>, d.operator ::std::basic_string_view<CharT, Traits>() 
            //             is not a valid expression.
            template <class R> 
            constexpr explicit basic_string_view (R&& r) : data_(std::ranges::data(r)), size_(std::ranges::size(r)) {
                static_assert(std::is_same_v<std::remove_cvref_t<R>, basic_string_view>, "R must not be basic_string_view");
                // static_assert()
                /// TODO: more static_asserts
            }

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