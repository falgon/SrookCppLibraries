// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_MATCH_CV_QUALIFIERS_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_MATCH_CV_QUALIFIERS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/is_const.hpp>
#include <srook/type_traits/is_volatile.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, bool, bool>
struct cv_selector;

template <class Unqualified>
struct cv_selector<Unqualified, false, false> : public type_constant<Unqualified> {};
template <class Unqualified>
struct cv_selector<Unqualified, false, true> : public type_constant<volatile Unqualified> {};
template <class Unqualified>
struct cv_selector<Unqualified, true, false> : public type_constant<const Unqualified> {};
template <class Unqualified>
struct cv_selector<Unqualified, true, true> : public type_constant<const volatile Unqualified> {};

} // namespace detail

template <class Qualified, class Unqualified, bool is_const = is_const<Qualified>::value, bool is_vol = is_volatile<Qualified>::value>
struct match_cv_qualifiers : public type_constant<SROOK_DEDUCED_TYPENAME detail::cv_selector<Unqualified, is_const, is_vol>::type> {};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

#endif
