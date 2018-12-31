// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_COMPARISON_SIZE_GEQ_HPP
#define INCLUDED_SROOK_TMPL_VT_COMPARISON_SIZE_GEQ_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/size_compare/eq.hpp>
#include <srook/tmpl/vt/size_compare/gt.hpp>
#include <srook/tmpl/vt/size.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class L, class R>
struct size_geq 
    : type_traits::detail::Lor<srook::tmpl::vt::size_eq<L, R>, srook::tmpl::vt::size_gt<L, R>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using size_geq_t = SROOK_DEDUCED_TYPENAME size_geq<L, R>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool size_geq_v = size_geq_t<L, R>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
