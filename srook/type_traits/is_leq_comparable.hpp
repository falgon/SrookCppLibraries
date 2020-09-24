// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_IS_LEQ_COMPARABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_IS_LEQ_COMPARABLE_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/declval.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T1, class T2>
struct is_leq_comparable_helper {
    template <class U1, class U2>
    static SROOK_DECLTYPE(declval<U1&>() <= declval<U2&>(), SROOK_TRUE_TYPE()) test(const U1&, const U2&);
    static SROOK_FALSE_TYPE test(...);
};

template <class T1, class T2>
struct is_nothrow_leq_comparable_helper {
    template <class U1, class U2>
    static bool_constant<noexcept(declval<U1&>() <= declval<U2&>())> test(const U1&, const U2&);
    static SROOK_FALSE_TYPE test(...);
};
} // namespace detail

template <class T, class U>
struct is_leq_comparable 
    : SROOK_DECLTYPE(detail::is_leq_comparable_helper<T, U>::test(declval<T>(), declval<U>())) {};
template <class T, class U>
struct is_nothrow_leq_comparable 
    : SROOK_DECLTYPE(detail::is_nothrow_leq_comparable_helper<T, U>::test(declval<T>(), declval<U>())) {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class U>
SROOK_CONSTEXPR bool is_leq_comparable_v = is_leq_comparable<T, U>::value;
template <class T, class U>
SROOK_CONSTEXPR bool is_nothrow_leq_comparable_v = is_nothrow_leq_comparable<T, U>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_leq_comparable;
using type_traits::is_nothrow_leq_comparable;

} // namespace srook

#endif
