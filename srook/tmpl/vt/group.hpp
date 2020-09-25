// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_GROUP_HPP
#define INCLUDED_SROOK_TMPL_VT_GROUP_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/group_by.hpp>
#include <srook/tmpl/vt/compare/eq.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class... Xs>
struct group : group_by<eq, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Xs>
using group_t = SROOK_DEDUCED_TYPENAME group<Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
