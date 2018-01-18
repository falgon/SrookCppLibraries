// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_HASH_MURMUR3_MURMUR3_HASH_HPP
#define INCLUDED_SROOK_HASH_MURMUR3_MURMUR3_HASH_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/hash/murmur3/detail/murmur3_traits.hpp>
#include <srook/hash/murmur3/detail/murmur3_impl.hpp>
#include <srook/tmpl/vt/is_contained_in.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/cstring/strlen.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/type_traits/remove_extent.hpp>
#include <srook/type_traits/is_unsigned.hpp>
#include <srook/type_traits/is_signed.hpp>
#include <srook/type_traits/make_unsigned.hpp>

SROOK_NESTED_NAMESPACE(srook, hash) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

typedef tmpl::vt::packer<std::string, std::wstring, std::u16string, std::u32string> std_string_pack;
#if SROOK_HAS_STD_STRING_VIEW
typedef tmpl::vt::packer<std::string_view, std::wstring_view, std::u16string_view, std::u32string_view> std_string_view_pack;
#endif
typedef tmpl::vt::packer<srook::string::string_view, srook::string::wstring_view, srook::string::u16string_view, srook::string::u32string_view> srook_string_view_pack;
typedef tmpl::vt::packer<char, wchar_t, char16_t, char32_t> fundamental_character_pack;

typedef 
    SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
        SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<std_string_pack, srook_string_view_pack>::type, fundamental_character_pack
        >::type
#if SROOK_HAS_STD_STRING_VIEW
        , std_string_view_pack
#endif
    >::type
    string_type_list;

template <class T>
struct is_valid_str 
    : public tmpl::vt::is_contained_in<
        SROOK_DEDUCED_TYPENAME remove_cv<SROOK_DEDUCED_TYPENAME remove_pointer<SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type, 
        string_type_list
      > {};

} // namespace detail

template <class String, typename Integral>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<type_traits::detail::Land<detail::is_valid_str<String>, is_integral<Integral>, is_unsigned<Integral>>::value, Integral>::type
murmur3(String key, std::size_t len, Integral seed)
{
    return detail::murmur3_impl(key, len, seed);
}

template <class String, typename Integral>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<type_traits::detail::Land<detail::is_valid_str<String>, is_integral<Integral>, is_signed<Integral>>::value, Integral>::type
murmur3(String key, std::size_t len, Integral seed)
{
    return murmur3(key, len, static_cast<SROOK_DEDUCED_TYPENAME make_unsigned<Integral>::type>(seed));
}

template <class String, typename Integral>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<type_traits::detail::Land<detail::is_valid_str<String>, is_integral<Integral>>::value, Integral>::type
murmur3(String key, Integral seed)
{
    return murmur3(key, cstring::strlen(key), seed);
}

template <class String, typename FloatingType>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        detail::is_valid_str<String>, 
        is_floating_point<FloatingType>
    >::value, 
    SROOK_DEDUCED_TYPENAME detail::murmur3_traits<sizeof(FloatingType)>::value_type
>::type
murmur3(String key, std::size_t len, FloatingType seed)
{
    // Still only support 32 bit
    return murmur3(key, len, static_cast<SROOK_DEDUCED_TYPENAME detail::murmur3_traits<sizeof(FloatingType)>::value_type>(seed));
}

template <class String, typename FloatingType>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        detail::is_valid_str<String>, 
        is_floating_point<FloatingType>
    >::value, 
    SROOK_DEDUCED_TYPENAME detail::murmur3_traits<sizeof(FloatingType)>::value_type
>::type
murmur3(String key, FloatingType seed)
{
    return murmur3(key, cstring::strlen(key), seed);
}

SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
detail::murmur3_traits<sizeof(srook::uint32_t)>::value_type 
operator"" _murmur332(const char* s, std::size_t len)
{
    return murmur3(s, len, 0);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(hash, srook)

#endif
#endif
