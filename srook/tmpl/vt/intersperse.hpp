// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_INTERSPERSE_HPP
#define INCLUDED_SROOK_TMPL_VT_INTERSPERSE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class...>
struct intersperse_impl;

template <class T>
struct intersperse_impl<T> : type_constant<packer<>> {};

template <class T, class X, class... Xs>
struct intersperse_impl<T, X, Xs...> 
    : concat<packer<X, T>, SROOK_DEDUCED_TYPENAME intersperse_impl<T, Xs...>::type> {};

template <class... XsL, class X, class... Xs>
struct intersperse_impl<packer<XsL...>, X, Xs...> 
    : concat<packer<X, XsL...>, SROOK_DEDUCED_TYPENAME intersperse_impl<packer<XsL...>, Xs...>::type> {};

} // namespace detail

template <class T, class... Xs>
struct intersperse : detail::intersperse_impl<T, Xs...> {};

template <class T, class... Xs>
struct intersperse<T, packer<Xs...>> : intersperse<T, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T, class... Xs>
using intersperse_t = SROOK_DEDUCED_TYPENAME intersperse<T, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
