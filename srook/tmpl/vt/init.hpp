// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_INIT_HPP
#define INCLUDED_SROOK_TMPL_VT_INIT_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/type_traits/type_constant.hpp>

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class...>
struct init;

template <class X>
struct init<X> : type_constant<packer<>> {};

template <class X, class... Xs>
struct init<X, Xs...> : concat<X, SROOK_DEDUCED_TYPENAME init<Xs...>::type> {};

template <class... Xs>
struct init<packer<Xs...>> : init<Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Xs>
using init_t = SROOK_DEDUCED_TYPENAME init<Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
