// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_MAKE_SIGNED_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_MAKE_SIGNED_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/is_enum.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/match_cv_qualifiers.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct make_unsigned_impl : public type_constant<T> {};

#define DEF_MAKE_UNSIGNED_IMPL(X) template <> struct make_unsigned_impl<X> : public type_constant<unsigned X> {}

DEF_MAKE_UNSIGNED_IMPL(char);
template <> struct make_unsigned_impl<signed char> : public make_unsigned_impl<char> {};
DEF_MAKE_UNSIGNED_IMPL(short);
DEF_MAKE_UNSIGNED_IMPL(int);
DEF_MAKE_UNSIGNED_IMPL(long);
DEF_MAKE_UNSIGNED_IMPL(long long);
#ifndef __WCHAR_UNSIGNED__
template <> struct make_unsigned_impl<wchar_t> : public make_unsigned_impl<__WCHAR_TYPE__> {};
#endif
#ifdef __GLIBCXX_TYPE_INT_N_0
DEF_MAKE_UNSIGNED_IMPL(__GLIBCXX_TYPE_INT_N_0);
#endif
#ifdef __GLIBCXX_TYPE_INT_N_1
DEF_MAKE_UNSIGNED_IMPL(__GLIBCXX_TYPE_INT_N_1);
#endif
#ifdef __GLIBCXX_TYPE_INT_N_2
DEF_MAKE_UNSIGNED_IMPL(__GLIBCXX_TYPE_INT_N_2);
#endif
#ifdef __GLIBCXX_TYPE_INT_N_3
DEF_MAKE_UNSIGNED_IMPL(__GLIBCXX_TYPE_INT_N_3);
#endif
#undef DEF_MAKE_UNSIGNED_IMPL

template <class T, bool is_int = is_integral<T>::value, bool is_enum = is_enum<T>::value>
class make_unsigned_selector;

template <class T>
struct make_unsigned_selector<T, true, false> 
    : public match_cv_qualifiers<T, SROOK_DEDUCED_TYPENAME make_unsigned_impl<SROOK_DEDUCED_TYPENAME remove_cv<T>::type>::type> {};

template <class T>
struct make_unsigned_selector<T, false, true> {
private:
    typedef unsigned char smallest_type;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST bool 
        b0 = sizeof(T) <= sizeof(smallest_type),
        b1 = sizeof(T) <= sizeof(unsigned short),
        b2 = sizeof(T) <= sizeof(unsigned int),
        b3 = sizeof(T) <= sizeof(unsigned long);
    typedef SROOK_DEDUCED_TYPENAME conditional<b3, unsigned long, unsigned long long>::type cond3;
    typedef SROOK_DEDUCED_TYPENAME conditional<b2, unsigned int, cond3>::type cond2;
    typedef SROOK_DEDUCED_TYPENAME conditional<b1, unsigned short, cond2>::type cond1;
    typedef SROOK_DEDUCED_TYPENAME conditional<b0, smallest_type, cond1>::type unsigned_type;
    typedef match_cv_qualifiers<T, unsigned_type> cv_unsigned;
public:
    typedef SROOK_DEDUCED_TYPENAME cv_unsigned::type type;
};

} // namespace detail

template <class T>
struct make_unsigned : public detail::make_unsigned_selector<T> {};

template <>
struct make_unsigned<bool> ;

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::make_unsigned;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using make_unsigned_t = SROOK_DEDUCED_TYPENAME make_unsigned<T>::type;
#endif

} // namespace srook

#endif
