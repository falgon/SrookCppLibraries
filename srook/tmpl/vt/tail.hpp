// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_TAIL_HPP
#define INCLUDED_SROOK_TMPL_VT_TAIL_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class...>
struct tail;

template <class X, class... Xs>
struct tail<X, Xs...> : type_constant<packer<Xs...>> {};

template <class... Xs>
struct tail<packer<Xs...>> : tail<Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Xs>
using tail_t = SROOK_DEDUCED_TYPENAME tail<Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
