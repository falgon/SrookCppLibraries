// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTRING_STRLEN_HPP
#define INCLUDED_SROOK_CSTRING_STRLEN_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/is_character.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/string/string_view.hpp>
#include <string>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT && SROOK_HAS_INCLUDE(<string_view>)
#   include <string_view>
#   define SROOK_HAS_STD_STRING_VIEW 1
#endif

SROOK_NESTED_NAMESPACE(srook, cstring) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <typename CharType>
SROOK_CONSTEXPR std::size_t strlen_impl(const CharType* s, std::size_t i)
{
    return *(s + i) == '\0' ? i : strlen_impl(s, i + 1);
}

} // namespace detail

template <typename CharType>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_character<CharType>::value, std::size_t>::type
strlen(const CharType* s)
{
    return *s == '\0' ? 0 : detail::strlen_impl(s, 1);
}

template <typename CharType>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME std::basic_string<CharType>::size_type
strlen(const std::basic_string<CharType>& s)
{
    return s.size();
}

#ifdef SROOK_HAS_STD_STRING_VIEW
template <typename CharType>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME std::basic_string_view<CharType>::size_type
strlen(const std::basic_string_view<CharType>& s)
{
    return s.size();
}
#endif

template <typename CharType>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME srook::string::basic_string_view<CharType>::size_type
strlen(const srook::string::basic_string_view<CharType>& s)
{
    return s.size();
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(cstring, srook)

#endif
