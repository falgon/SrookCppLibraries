// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_POSTINCREMENTABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_POSTINCREMENTABLE_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/declval.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_postincrementable_helper {
    template <class U>
    static SROOK_DECLTYPE(declval<U&>()++, SROOK_TRUE_TYPE()) test(const U&);
    static SROOK_FALSE_TYPE test(...);
};

} // namespace detail

template <class T>
struct is_postincrementable 
    : SROOK_DECLTYPE(detail::is_postincrementable_helper<T>::test(declval<T>())) {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_postincrementable_v = is_postincrementable<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_postincrementable;
using type_traits::is_postincrementable_v;

} // namespace srook

#endif
