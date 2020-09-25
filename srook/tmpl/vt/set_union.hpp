// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_SET_UNION_HPP
#define INCLUDED_SROOK_TMPL_VT_SET_UNION_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/unique.hpp>
#include <srook/type_traits/type_constant.hpp>

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class L, class R>
struct set_union : unique<SROOK_DEDUCED_TYPENAME concat<L, R>::type> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using set_union_t = SROOK_DEDUCED_TYPENAME set_union<L, R>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
