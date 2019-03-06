// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_UNSIGNED_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_UNSIGNED_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/type_traits/bool_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, bool = is_arithmetic<T>::value>
struct is_unsigned : bool_constant<T(0) < T(-1)> {};

template <class T>
struct is_unsigned<T, false> : SROOK_FALSE_TYPE {};

} // namespace detail

template <class T>
struct is_unsigned : public detail::is_unsigned<T>::type {};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_unsigned;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_unsigned_v = is_unsigned<T>::value;
#endif

} // namespace srook

#endif
