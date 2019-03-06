// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_POSTDECREMENTABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_POSTDECREMENTABLE_HPP
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
struct is_postdecrementable_helper {
    template <class U>
    static SROOK_DECLTYPE(declval<U&>()--, SROOK_TRUE_TYPE()) test(const U&);
    static SROOK_FALSE_TYPE test(...);
};

template <class T>
struct is_nothrow_postdecrementable_helper {
    template <class U>
    static bool_constant<noexcept(declval<U&>()--)> test(const U&);
    static SROOK_FALSE_TYPE test(...);
};
} // namespace detail

template <class T>
struct is_postdecrementable 
    : SROOK_DECLTYPE(detail::is_postdecrementable_helper<T>::test(declval<T>())) {};
template <class T>
struct is_nothrow_postdecrementable 
    : SROOK_DECLTYPE(detail::is_nothrow_postdecrementable_helper<T>::test(declval<T>())) {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_postdecrementable_v = is_postdecrementable<T>::value;
template <class T>
SROOK_CONSTEXPR bool is_nothrow_postdecrementable_v = is_nothrow_postdecrementable<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_postdecrementable;
using type_traits::is_nothrow_postdecrementable;

} // namespace srook

#endif
