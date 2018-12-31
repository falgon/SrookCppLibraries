// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_INCREMENTABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_INCREMENTABLE_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_preincrementable.hpp>
#include <srook/type_traits/is_postincrementable.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_incrementable : type_traits::detail::Land<is_preincrementable<T>, is_postincrementable<T>> {};
template <class T>
struct is_nothrow_incrementable : type_traits::detail::Land<is_nothrow_preincrementable<T>, is_nothrow_postincrementable<T>> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_incrementable_v = is_incrementable<T>::value;
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_incrementable_v = is_nothrow_incrementable<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_incrementable;
using srook::type_traits::is_nothrow_incrementable;

} // namespace srook

#endif
