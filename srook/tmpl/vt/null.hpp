// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_NULL_HPP
#define INCLUDED_SROOK_TMPL_VT_NULL_HPP

#ifndef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class...>
struct null;

template <class X, class... Xs>
struct null<X, Xs...> : type_constant<SROOK_FALSE_TYPE> {};

template <>
struct null<> : type_constant<SROOK_TRUE_TYPE> {};

template <class... Xs>
struct null<packer<Xs...>> : null<Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Xs>
using null_t = SROOK_DEDUCED_TYPENAME null<Xs...>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class... Ts>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool null_v = null_t<Ts...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
