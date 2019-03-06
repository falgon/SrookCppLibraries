// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_PREINCREMENTABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_PREINCREMENTABLE_HPP
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

template <class T>
struct is_preincrementable_helper {
    template <class U>
    static SROOK_DECLTYPE(++declval<U&>(), SROOK_TRUE_TYPE()) test(const U&);
    static SROOK_FALSE_TYPE test(...);
};

template <class T>
struct is_nothrow_preincrementable_helper {
    template <class U>
    static bool_constant<noexcept(++declval<U&>())> test(const U&);
    static SROOK_FALSE_TYPE test(...);
};

} // namespace detail

template <class T>
struct is_preincrementable 
    : SROOK_DECLTYPE(detail::is_preincrementable_helper<T>::test(declval<T>())) {};
template <class T>
struct is_nothrow_preincrementable 
    : SROOK_DECLTYPE(detail::is_nothrow_preincrementable_helper<T>::test(declval<T>())) {};

#if SROOK_CPP_VARIADIC_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_preincrementable_v = is_preincrementable<T>::value;
template <class T>
SROOK_CONSTEXPR bool is_nothrow_preincrementable_v = is_nothrow_preincrementable<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_preincrementable;
using type_traits::is_nothrow_preincrementable;

} // namespace srook

#endif
