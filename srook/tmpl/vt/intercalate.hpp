// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_INTERCALATE_HPP
#define INCLUDED_SROOK_TMPL_VT_INTERCALATE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/intersperse.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, class...>
struct intercalate;

template <class... T, class... Xs>
struct intercalate<packer<T...>, Xs...> : intersperse<packer<T...>, Xs...> {};

template <class... T, class... Xs>
struct intercalate<packer<T...>, packer<Xs...>> : intercalate<packer<T...>, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T, class... Xs>
using intercalate_t = SROOK_DEDUCED_TYPENAME intercalate<T, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
