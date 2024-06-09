#ifndef STRING_VIEW_ALIASES_HPP
#define STRING_VIEW_ALIASES_HPP

#include "string_view.hpp"

namespace bsv {

using string_view = basic_string_view<char>;
using wstring_view = basic_string_view<wchar_t>;
using u8string_view = basic_string_view<char8_t>;
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;

} // namespace bsv

#endif // STRING_VIEW_ALIASES_HPP
