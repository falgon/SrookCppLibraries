// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_COMPARISON_LEQ_HPP
#define INCLUDED_SROOK_TMPL_VT_COMPARISON_LEQ_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/compare/eq.hpp>
#include <srook/tmpl/vt/compare/lt.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class L, class R>
struct leq 
    : type_traits::detail::Lor<srook::tmpl::vt::eq<L, R>, srook::tmpl::vt::lt<L, R>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using leq_t = SROOK_DEDUCED_TYPENAME leq<L, R>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool leq_v = leq_t<L, R>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
