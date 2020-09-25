// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_RANGE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_RANGE_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/has_iterator.hpp>
#include <srook/type_traits/is_array.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_range : ::srook::type_traits::detail::Lor<has_iterator<T>, is_array<T>> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_range_v = is_range<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

namespace srook {

using srook::type_traits::is_range;

} // namespace srook
#endif
