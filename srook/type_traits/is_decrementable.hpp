// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_DECREMENTABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_DECREMENTABLE_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_predecrementable.hpp>
#include <srook/type_traits/is_postdecrementable.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_decrementable : type_traits::detail::Land<is_predecrementable<T>, is_postdecrementable<T>> {};
template <class T>
struct is_nothrow_decrementable : type_traits::detail::Land<is_nothrow_predecrementable<T>, is_nothrow_postdecrementable<T>> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_decrementable_v = is_decrementable<T>::value;
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_decrementable_v = is_nothrow_decrementable<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_decrementable;
using srook::type_traits::is_nothrow_decrementable;

} // namespace srook

#endif
