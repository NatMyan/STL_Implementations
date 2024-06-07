#include "string_view.hpp"

#include <limits>

namespace bsv {
    // Iterators ---------------------------------------------------------------------------------------------------------------------
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_iterator basic_string_view<CharT, Traits>::begin() const noexcept {
        return const_iterator(data_);
    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_iterator basic_string_view<CharT, Traits>::cbegin() const noexcept {
        return const_iterator(data_);
    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_iterator basic_string_view<CharT, Traits>::end() const noexcept {
        return const_iterator(data_ + size_);
    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_iterator basic_string_view<CharT, Traits>::cend() const noexcept {
        return const_iterator(data_ + size_);
    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_reverse_iterator basic_string_view<CharT, Traits>::rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_reverse_iterator basic_string_view<CharT, Traits>::crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_reverse_iterator basic_string_view<CharT, Traits>::rend() const noexcept {
        return const_reverse_iterator(begin());
    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_reverse_iterator basic_string_view<CharT, Traits>::crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }


    // Element access ----------------------------------------------------------------------------------------------------------------
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_reference basic_string_view<CharT, Traits>::operator[] (size_type pos) const {
        return *(data_ + pos);
    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_reference basic_string_view<CharT, Traits>::at (size_type pos) const {
        if (pos >= size_) {
            throw std::out_of_range("basic_string_view::at: pos out of range");
        }
        return *(data_ + pos);
    }   

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_reference basic_string_view<CharT, Traits>::front() const {
        return *data_;
    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_reference basic_string_view<CharT, Traits>::back() const {
        return *(data_ + size_ - 1);
    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::const_pointer basic_string_view<CharT, Traits>::data() const noexcept {
        return data_;
    }


    // Capacity ----------------------------------------------------------------------------------------------------------------------
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::size() const noexcept {
        return size_;
        // return std::distance(begin(), end()); 
        /// TODO: which one ?
    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::length() const noexcept {
        return size_;
        // return std::distance(begin(), end());
        /// TODO: which one ?
    }

    // Returns the maximum number of characters
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::max_size() const noexcept {
        return std::numeric_limits<size_type>::max();
    }

    template <typename CharT, typename Traits> 
    [[nodiscard]] constexpr bool basic_string_view<CharT, Traits>::empty() const noexcept {
        return size() == 0;
        /// TODO: check if data_ is nullptr or not?
    }
    

    // Modifiers ---------------------------------------------------------------------------------------------------------------------
    
    // Moves the start of the view forward by n characters.
    // The behavior is undefined if n > size(). 
    template <typename CharT, typename Traits> 
    constexpr void basic_string_view<CharT, Traits>::remove_prefix (size_type n) {
        data_ += n;
        size_ -= n;
    }

    // Moves the end of the view back by n characters.
    // The behavior is undefined if n > size(). 
    template <typename CharT, typename Traits> 
    constexpr void basic_string_view<CharT, Traits>::remove_suffix (size_type n) {
        size_ -= n;
    }

    // Exchanges the view with that of v. 
    template <typename CharT, typename Traits> 
    constexpr void basic_string_view<CharT, Traits>::swap (basic_string_view& v) noexcept {
        using std::swap;  // more readable and efficient, I guess
        swap(this->data_, v.data_);
        swap(this->size_, v.size_);

        // auto tempData = this->data_;
        // this->data_ = v.data_;
        // v.data_ = tempData;
        // auto tempSize = this->size_;
        // this->size_ = v.size_;
        // v.size_ = tempSize;
    }

    // Operations --------------------------------------------------------------------------------------------------------------------

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::copy (CharT* dest, size_type count, size_type pos = 0) const {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits> basic_string_view<CharT, Traits>::substr (size_type pos = 0, size_type count = npos) const {

    }

    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (basic_string_view v) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (size_type pos1, size_type count1, basic_string_view v) const {

    }

    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2) const {

    }

    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (const CharT* s) const {

    }

    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (size_type pos1, size_type count1, const CharT* s) const {

    }

    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (size_type pos1, size_type count1, const CharT* s, size_type count2) const {

    }

    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::starts_with (basic_string_view sv) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::starts_with (CharT ch) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::starts_with (const CharT* s) const {

    }

    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::ends_with (basic_string_view sv) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::ends_with (CharT ch) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::ends_with (const CharT* s) const {

    }

    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::contains (basic_string_view sv) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::contains (CharT c) const noexcept {

    }
    
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::contains (const CharT* s) const {

    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find (basic_string_view v, size_type pos = 0) const noexcept {

    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find (CharT ch, size_type pos = 0) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find (const CharT* s, size_type pos, size_type count) const {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find (const CharT* s, size_type pos = 0) const {

    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::rfind (basic_string_view v, size_type pos = npos) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::rfind (CharT ch, size_type pos = npos) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::rfind (const CharT* s, size_type pos, size_type count) const {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::rfind (const CharT* s, size_type pos = npos) const {

    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_of (basic_string_view v, size_type pos = 0) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_of (CharT ch, size_type pos = 0) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_of (const CharT* s, size_type pos, size_type count) const {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_of (const CharT* s, size_type pos = 0) const {

    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_of (basic_string_view v, size_type pos = npos) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_of (CharT ch, size_type pos = npos) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_of (const CharT* s, size_type pos, size_type count) const {

    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_of (const CharT* s, size_type pos = npos) const {

    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_not_of (basic_string_view v, size_type pos = 0) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_not_of (CharT ch, size_type pos = 0) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_not_of (const CharT* s, size_type pos, size_type count) const {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_not_of (const CharT* s, size_type pos = 0) const {

    }
    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_not_of (basic_string_view v, size_type pos = npos) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_not_of (CharT ch, size_type pos = npos) const noexcept {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_not_of (const CharT* s, size_type pos, size_type count) const {

    }

    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_not_of (const CharT* s, size_type pos = npos) const {

    }


} // namespace bsv