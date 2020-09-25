// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_COMPARABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_COMPARABLE_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_lt_comparable.hpp>
#include <srook/type_traits/is_leq_comparable.hpp>
#include <srook/type_traits/is_gt_comparable.hpp>
#include <srook/type_traits/is_geq_comparable.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class U>
struct is_comparable 
    : type_traits::detail::Land<is_lt_comparable<T, U>, is_leq_comparable<T, U>, is_gt_comparable<T, U>, is_geq_comparable<T, U>> {};
template <class T, class U>
struct is_nothrow_comparable 
    : type_traits::detail::Land<is_nothrow_lt_comparable<T, U>, is_nothrow_leq_comparable<T, U>, is_nothrow_gt_comparable<T, U>, is_nothrow_geq_comparable<T, U>> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class U>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_comparable_v = is_comparable<T, U>::value;
template <class T, class U>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_comparable_v = is_nothrow_comparable<T, U>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_comparable;
using srook::type_traits::is_nothrow_comparable;

} // namespace srook

#endif
