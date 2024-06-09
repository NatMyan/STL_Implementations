#ifndef STRING_VIEW_IMPL_HPP
#define STRING_VIEW_IMPL_HPP

#include "string_view.hpp"

#include <iostream>
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

    // Copies the substring [pos, pos + rcount) to the character array pointed to by dest, where rcount is the smaller of 
    // count and size() - pos. 
    // Equivalent to Traits::copy(dest, data() + pos, rcount). 
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::copy (CharT* dest, size_type count, size_type pos) const {
        if (pos > size_) {
            throw std::out_of_range("basic_string_view::copy: pos out of range");
        }
        size_type rcount = std::min(count, size() - pos);
        Traits::copy(dest, data() + pos, rcount);
        return rcount; 
        /// TODO: or rcount + 1;
    }

    // Returns a view of the substring [pos, pos + rlen), where rlen is the smaller of count and size() - pos. 
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits> basic_string_view<CharT, Traits>::substr (size_type pos, size_type count) const {
        if (pos > size_) {
            throw std::out_of_range("basic_string_view::substr: pos out of range");
        }
        size_type rlen = std::min(count, size() - pos);
        return basic_string_view(data_ + pos, rlen);
    }

    // The length rlen of the sequences to compare is the smaller of size() and v.size(). The function compares the two views by 
    // calling traits::compare(data(), v.data(), rlen), and returns a value according to the following table:
    // |---------------------------------------------------------------------|--------------------------|----------------|
    // |                              Condition                              |          Result          |  Return value  |
    // |---------------------------------------------------------------------|--------------------------|----------------|
    // | Traits::compare(data(), v.data(), rlen) < 0 	                     | this is less than v 	    |      < 0       |  
    // |---------------------------------------------------------------------|--------------------------|----------------|
    // | Traits::compare(data(), v.data(), rlen) == 0 |  size() < v.size() 	 | this is less than v 	    |      < 0       |
    // |                                              |  size() == v.size()  | this is equal to v 	    |      ​0​         |
    // |                                              |  size() > v.size()   | this is greater than v 	|      > 0       |
    // |---------------------------------------------------------------------|--------------------------|----------------|
    // | Traits::compare(data(), v.data(), rlen) > 0 	                     | this is greater than v 	|      > 0       |
    // |---------------------------------------------------------------------|--------------------------|----------------|
    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (basic_string_view v) const noexcept {
        size_type rlen = std::min(size_, v.size_);
        int res = Traits::compare(data_, v.data_, rlen);
        
        if (res != 0) { return res; }
        if (size_ < v.size_) { return -1; }
        if (size_ > v.size_) { return 1; }
        return 0;
    }

    // Equivalent to substr(pos1, count1).compare(v).
    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (size_type pos1, size_type count1, basic_string_view v) const {
        return substr(pos1, count1).compare(v);
    }
    
    // Equivalent to substr(pos1, count1).compare(v.substr(pos2, count2)).
    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2) const {
        return substr(pos1, count1).compare(v.substr(pos2, count2));
    }

    // Equivalent to compare(basic_string_view(s)).
    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (const CharT* s) const {
        return compare(basic_string_view(s));
    }

    // Equivalent to substr(pos1, count1).compare(basic_string_view(s)).
    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (size_type pos1, size_type count1, const CharT* s) const {
        return substr(pos1, count1).compare(basic_string_view(s));
    }

    // Equivalent to substr(pos1, count1).compare(basic_string_view(s, count2)).
    template <typename CharT, typename Traits> 
    constexpr int basic_string_view<CharT, Traits>::compare (size_type pos1, size_type count1, const CharT* s, size_type count2) const {
        return substr(pos1, count1).compare(basic_string_view(s, count2));
    }

    // Checks if the string view begins with the given prefix, where the prefix is a string view. Effectively returns 
    // basic_string_view(data(), std::min(size(), sv.size())) == sv.
    // sv 	- 	a string view which may be a result of implicit conversion from std::basic_string
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::starts_with (basic_string_view sv) const noexcept {
        return basic_string_view(data(), std::min(size(), sv.size())) == sv;
    }
    
    // Checks if the string view begins with the given prefix, where the prefix is a single character. Effectively returns 
    // !empty() && Traits::eq(front(), ch).
    // ch 	- 	a single character
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::starts_with (CharT ch) const noexcept {
        return !empty() && Traits::eq(front(), ch);
    }

    // Checks if the string view begins with the given prefix, where the prefix is a null-terminated character string. 
    // Effectively returns starts_with(basic_string_view(s)).
    // s 	- 	a null-terminated character string 
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::starts_with (const CharT* s) const {
        return starts_with(basic_string_view(s));
    }

    // Checks if the string view ends with the given suffix, where the suffix is a string view. Effectively returns 
    // size() >= sv.size() && compare(size() - sv.size(), npos, sv) == 0.
    // sv 	- 	a string view which may be a result of implicit conversion from std::basic_string
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::ends_with (basic_string_view sv) const noexcept {
        return size() >= sv.size() && compare(size() - sv.size(), npos, sv) == 0;
    }
    
    // Checks if the string view ends with the given suffix, where the suffix is a single character. Effectively returns 
    // !empty() && Traits::eq(back(), ch).
    // ch 	- 	a single character
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::ends_with (CharT ch) const noexcept {
        return !empty() && Traits::eq(back(), ch);
    }   

    // Checks if the string view ends with the given suffix, where the suffix is a single character. Effectively returns 
    // ends_with(basic_string_view(s)).
    // s 	- 	a null-terminated character string 
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::ends_with (const CharT* s) const {
        return ends_with(basic_string_view(s));
    }

    // Checks if the string view contains the given substring, where the substring is a string view.
    // sv 	- 	a string view    
    // Equivalent to return find(x) != npos;, where x is the parameter. 
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::contains (basic_string_view sv) const noexcept {
        return find(sv) != npos;
    }

    // Checks if the string view contains the given substring, where the substring is a single character.
    // c 	- 	a single character
    // Equivalent to return find(x) != npos;, where x is the parameter. 
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::contains (CharT c) const noexcept {
        return find(c) != npos;
    }
    
    // Checks if the string view contains the given substring, where the substring is a null-terminated character string.
    // s 	- 	a null-terminated character string 
    // Equivalent to return find(x) != npos;, where x is the parameter. 
    template <typename CharT, typename Traits> 
    constexpr bool basic_string_view<CharT, Traits>::contains (const CharT* s) const {
        return find(s) != npos;
    }
    
    // Finds the first occurence of v in this view, starting at position pos.
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find (basic_string_view v, size_type pos) const noexcept {
        if (pos > size_ || v.size_ > size_) { return npos; }
        if (v.size_ == 0) { return pos; } 
        for (size_type i = pos; i <= size_ - v.size_; ++i) {
            if (Traits::compare(data_ + i, v.data_, v.size_) == 0) {
                return i;
            }
        }
        return npos;
    }
    
    // Equivalent to find(basic_string_view(std::addressof(ch), 1), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find (CharT ch, size_type pos) const noexcept {
        return find(basic_string_view(std::addressof(ch), 1), pos);
    }

    // Equivalent to find(basic_string_view(s, count), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find (const CharT* s, size_type pos, size_type count) const {
        return find(basic_string_view(s, count), pos);
    }

    // Equivalent to find(basic_string_view(s), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find (const CharT* s, size_type pos) const {
        return find(basic_string_view(s), pos);
    }
    
    // Finds the last substring that is equal to the given character sequence. The search begins at pos and proceeds from right to 
    // left (thus, the found substring, if any, cannot begin in a position following pos). If npos or any value not smaller than 
    // size() - 1 is passed as pos, the whole string will be searched. 
    // Finds the last occurrence of v in this view, starting at position pos.
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::rfind (basic_string_view v, size_type pos) const noexcept {
        if (v.size_ > size_) { return npos; } 
        if (v.size_ == 0) { return pos; }

        if (pos > size_) { pos = size_; }

        // Start from the last possible position where v can fit in the string view
        const size_type start_pos = (size_ - v.size_ < pos ? size_ - v.size_ : pos);
        for (size_type i = start_pos + 1; i > 0; --i) {
            /// TODO: is --i correct here ?
            if (Traits::compare(data_ + i, v.data_, v.size_) == 0) {
                return i; 
            }
        }
        return npos; 
        /// TODO: is this correct?
    }

    // Finds the last substring that is equal to the given character sequence. The search begins at pos and proceeds from right to 
    // left (thus, the found substring, if any, cannot begin in a position following pos). If npos or any value not smaller than 
    // size() - 1 is passed as pos, the whole string will be searched. 
    // Equivalent to rfind(basic_string_view(std::addressof(ch), 1), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::rfind (CharT ch, size_type pos) const noexcept {
        return rfind(basic_string_view(std::addressof(ch), 1), pos);
    }

    // Finds the last substring that is equal to the given character sequence. The search begins at pos and proceeds from right to 
    // left (thus, the found substring, if any, cannot begin in a position following pos). If npos or any value not smaller than 
    // size() - 1 is passed as pos, the whole string will be searched. 
    // Equivalent to rfind(basic_string_view(s, count), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::rfind (const CharT* s, size_type pos, size_type count) const {
        return rfind(basic_string_view(s, count), pos);
    }

    // Finds the last substring that is equal to the given character sequence. The search begins at pos and proceeds from right to 
    // left (thus, the found substring, if any, cannot begin in a position following pos). If npos or any value not smaller than 
    // size() - 1 is passed as pos, the whole string will be searched. 
    // Equivalent to rfind(basic_string_view(s), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::rfind (const CharT* s, size_type pos) const {
        return rfind(basic_string_view(s), pos);
    }
    
    // Finds the first character equal to any of the characters in the given character sequence.
    // Finds the first occurrence of any of the characters of v in this view, starting at position pos.
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_of (basic_string_view v, size_type pos) const noexcept {
        if (pos >= size_) { return npos; }

        for (size_type i = pos; i < size_; ++i) {
            for (size_type j = 0; j < v.size_; ++j) {
                if (Traits::eq(data_[i], v.data_[j])) {
                    return i;
                }
            }
        }
        return npos;
    }

    // Finds the first character equal to any of the characters in the given character sequence.
    // Equivalent to find_first_of(basic_string_view(std::addressof(ch), 1), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_of (CharT ch, size_type pos) const noexcept {
        return find_first_of(basic_string_view(std::addressof(ch), 1), pos);
    }

    // Finds the first character equal to any of the characters in the given character sequence.
    // Equivalent to find_first_of(basic_string_view(s, count), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_of (const CharT* s, size_type pos, size_type count) const {
        return find_first_of(basic_string_view(s, count), pos);
    }

    // Finds the first character equal to any of the characters in the given character sequence.
    // Equivalent to find_first_of(basic_string_view(s), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_of (const CharT* s, size_type pos) const {
        return find_first_of(basic_string_view(s), pos);
    }
    
    // Finds the last character equal to one of characters in the given character sequence. Exact search algorithm is not specified. 
    // The search considers only the interval [​0​, pos]. If the character is not present in the interval, npos will be returned.
    // Finds the last occurence of any of the characters of v in this view, ending at position pos.
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_of (basic_string_view v, size_type pos) const noexcept {
        if (pos >= size_) { pos = size_ - 1; }
        for (size_type i = pos; i >= 0; --i) { 
            bool found = false;
            for (size_type j = 0; j < v.size_; ++j) {
                if (Traits::eq(data_[i], v.data_[j])) {
                    found = true;
                    break;
                }
            }
            if (found) {
                return i;
            }
        }
        return npos;
        // for (size_type i = pos; i >= 0; --i) { 
        //     /// TODO: is --i correct here ?
        //     for (size_type j = 0; j < v.size_; ++j) {
        //         if (Traits::eq(data_[i], v.data_[j])) {
        //             return i;
        //         }
        //     }
        // }
        // return npos;
    }

    // Finds the last character equal to one of characters in the given character sequence. Exact search algorithm is not specified. 
    // The search considers only the interval [​0​, pos]. If the character is not present in the interval, npos will be returned.
    // Equivalent to find_last_of(basic_string_view(std::addressof(ch), 1), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_of (CharT ch, size_type pos) const noexcept {
        return find_last_of(basic_string_view(std::addressof(ch), 1), pos);
    }

    // Finds the last character equal to one of characters in the given character sequence. Exact search algorithm is not specified. 
    // The search considers only the interval [​0​, pos]. If the character is not present in the interval, npos will be returned.
    // Equivalent to find_last_of(basic_string_view(s, count), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_of (const CharT* s, size_type pos, size_type count) const {
        return find_last_of(basic_string_view(s, count), pos);
    }
    
    // Finds the last character equal to one of characters in the given character sequence. Exact search algorithm is not specified. 
    // The search considers only the interval [​0​, pos]. If the character is not present in the interval, npos will be returned.
    // Equivalent to find_last_of(basic_string_view(s), pos).    
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_of (const CharT* s, size_type pos) const {
        return find_last_of(basic_string_view(s), pos);
    }
    
    // Finds the first character not equal to any of the characters in the given character sequence.
    // Finds the first character not equal to any of the characters of v in this view, starting at position pos.
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_not_of (basic_string_view v, size_type pos) const noexcept {
        if (pos >= size_) { return npos; }

        for (size_type i = pos; i < size_; ++i) {
            bool found = false;
            for (size_type j = 0; j < v.size_; ++j) {
                if (Traits::eq(data_[i], v.data_[j])) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return i;
            }
        }
        return npos;

        // for (size_type i = pos; i < size_; ++i) {
        //     for (size_type j = 0; j < v.size_; ++j) {
        //         if (!Traits::eq(data_[i], v.data_[j])) {
        //             return i;
        //         }
        //     }
        // }
        // return npos;
    }

    // Finds the first character not equal to any of the characters in the given character sequence.
    // Equivalent to find_first_not_of(basic_string_view(std::addressof(ch), 1), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_not_of (CharT ch, size_type pos) const noexcept {
        return find_first_not_of(basic_string_view(std::addressof(ch), 1), pos);
    }  

    // Finds the first character not equal to any of the characters in the given character sequence.
    // Equivalent to find_first_not_of(basic_string_view(s, count), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_not_of (const CharT* s, size_type pos, size_type count) const {
        return find_first_not_of(basic_string_view(s, count), pos);
    }

    // Finds the first character not equal to any of the characters in the given character sequence.
    // Equivalent to find_first_not_of(basic_string_view(s), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_first_not_of (const CharT* s, size_type pos) const {
        return find_first_not_of(basic_string_view(s), pos);
    }
    
    // Finds the last character not equal to any of the characters in the given character sequence. The search considers only 
    // the interval [​0​, pos].
    // Finds the last character not equal to any of the characters of v in this view, starting at position pos.
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_not_of (basic_string_view v, size_type pos) const noexcept {
        if (pos >= size_) { pos = size_ - 1; }
        for (size_type i = pos; i >= 0; --i) {
            bool found = false;
            for (size_type j = 0; j < v.size_; ++j) {
                if (Traits::eq(data_[i], v.data_[j])) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return i;
            }
        }
        return npos;

        // for (size_type i = pos; i <= 0; --i) { 
        //     /// TODO: is --i correct here ?
        //     for (size_type j = 0; j < v.size_; ++j) {
        //         if (!Traits::eq(data_[i], v.data_[j])) {
        //             return i;
        //         }
        //     }
        // }
        // return npos;
    }

    // Finds the last character not equal to any of the characters in the given character sequence. The search considers only 
    // the interval [​0​, pos].
    // Equivalent to find_last_not_of(basic_string_view(std::addressof(ch), 1), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_not_of (CharT ch, size_type pos) const noexcept {
        return find_last_not_of(basic_string_view(std::addressof(ch), 1), pos);
    }

    // Finds the last character not equal to any of the characters in the given character sequence. The search considers only 
    // the interval [​0​, pos].
    // Equivalent to find_last_not_of(basic_string_view(s, count), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_not_of (const CharT* s, size_type pos, size_type count) const {
        return find_last_not_of(basic_string_view(s, count), pos);
    }

    // Finds the last character not equal to any of the characters in the given character sequence. The search considers only 
    // the interval [​0​, pos].
    // Equivalent to find_last_not_of(basic_string_view(s), pos).
    template <typename CharT, typename Traits> 
    constexpr basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::find_last_not_of (const CharT* s, size_type pos) const {
        return find_last_not_of(basic_string_view(s), pos);
    }

    template< class CharT, class Traits >
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, basic_string_view<CharT, Traits> v){
        return os.write(v.data(), v.size());
    }

    // template< class CharT, class Traits >
    // std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, std::basic_string_view<CharT, Traits> v){
    //     for (const CharT* ptr = v.data(); ptr < v.data() + v.size(); ++ptr) {
    //         os.put(*ptr);
    //     }
    //     return os;
    // }

    template< class CharT, class Traits >
    constexpr bool operator== (basic_string_view<CharT,Traits> lhs, std::type_identity_t<basic_string_view<CharT,Traits> > rhs) noexcept {
        return lhs.data() == rhs.data() && lhs.size() == rhs.size();
    }

    

} // namespace bsv

#endif // STRING_VIEW_IMPL_HPP