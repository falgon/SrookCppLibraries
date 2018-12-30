// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_COMPARISON_SIZE_EQ_HPP
#define INCLUDED_SROOK_TMPL_VT_COMPARISON_SIZE_EQ_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/size.hpp>
#include <srook/tmpl/vt/compare/eq.hpp>
#include <srook/type_traits/bool_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class L, class R>
struct size_eq : eq<L, R>::type {};

template <class... L, class... R>
struct size_eq<packer<L...>, packer<R...>> : bool_constant<size<packer<L...>>::value == size<packer<R...>>::value> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using size_eq_t = SROOK_DEDUCED_TYPENAME size_eq<L, R>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool size_eq_v = size_eq_t<L, R>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
