// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_COMPARISON_NEQ_HPP
#define INCLUDED_SROOK_TMPL_VT_COMPARISON_NEQ_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/compare/eq.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class L, class R>
struct neq : type_traits::detail::Lnot<eq<L, R>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using neq_t = SROOK_DEDUCED_TYPENAME neq<L, R>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool neq_v = neq_t<L, R>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
