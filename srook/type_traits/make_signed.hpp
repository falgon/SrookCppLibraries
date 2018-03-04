// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_MAKE_SIGNED_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_MAKE_SIGNED_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/type_traits/make_unsigned.hpp>
#include <srook/cstdint.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct make_signed_impl : public type_constant<T> {};

#if defined(SROOK_HAS_INT128) && !defined(__STRICT_ANSI__)
template <>
struct make_signed_impl<srook::int128_t> : public type_constant<srook::int128_t> {};
template <>
struct make_signed_impl<srook::uint128_t> : public type_constant<srook::int128_t> {};
#endif

#define DEF_MAKE_SIGNED_IMPL(X) template <> struct make_signed_impl<unsigned X> : public type_constant<signed X> {}

DEF_MAKE_SIGNED_IMPL(char);
template <> struct make_signed_impl<char> : public make_signed_impl<unsigned char> {};
DEF_MAKE_SIGNED_IMPL(short);
DEF_MAKE_SIGNED_IMPL(int);
DEF_MAKE_SIGNED_IMPL(long);
DEF_MAKE_SIGNED_IMPL(long long);
#ifdef __WCHAR_UNSIGNED__
template <> struct make_signed_impl<wchar_t> : public make_signed_impl<__WCHAR_TYPE__> {};
#endif
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <>
struct make_signed_impl<char16_t> : make_signed_impl<uint_least16_t> {};
template <>
struct make_signed_impl<char32_t> : make_signed_impl<uint_least32_t> {};
#endif

#ifdef __GLIBCXX_TYPE_INT_N_0
DEF_MAKE_SIGNED_IMPL(__GLIBCXX_TYPE_INT_N_0);
#endif
#ifdef __GLIBCXX_TYPE_INT_N_1
DEF_MAKE_SIGNED_IMPL(__GLIBCXX_TYPE_INT_N_1);
#endif
#ifdef __GLIBCXX_TYPE_INT_N_2
DEF_MAKE_SIGNED_IMPL(__GLIBCXX_TYPE_INT_N_2);
#endif
#ifdef __GLIBCXX_TYPE_INT_N_3
DEF_MAKE_SIGNED_IMPL(__GLIBCXX_TYPE_INT_N_3);
#endif
#undef DEF_MAKE_SIGNED_IMPL

template <class T, bool is_int = is_integral<T>::value, bool is_enum = is_enum<T>::value>
class make_signed_selector;

template <class T>
struct make_signed_selector<T, true, false> 
    : public match_cv_qualifiers<T, SROOK_DEDUCED_TYPENAME make_signed_impl<SROOK_DEDUCED_TYPENAME remove_cv<T>::type>::type> {};

template <class T>
struct make_signed_selector<T, false, true> 
    : public make_signed_selector<SROOK_DEDUCED_TYPENAME make_unsigned_selector<T>::type> {}; 

} // namespace detail

template <class T>
struct make_signed : public detail::make_signed_selector<T> {};

template <>
struct make_signed<bool> ;

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::make_signed;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using make_signed_t = SROOK_DEDUCED_TYPENAME make_signed<T>::type;
#endif

} // namespace srook

#endif
