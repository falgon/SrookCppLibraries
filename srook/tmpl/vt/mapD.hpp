// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_MAPD_HPP
#define INCLUDED_SROOK_TMPL_VT_MAPD_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/cons.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class...>
struct mapD_impl;

template <class F>
struct mapD_impl<F> : type_constant<packer<>> {};

template <class F, class X, class... Xs>
struct mapD_impl<F, X, Xs...> 
    : cons<SROOK_DEDUCED_TYPENAME F::template type<X>::result_type, SROOK_DEDUCED_TYPENAME mapD_impl<F, Xs...>::type> {};

template <class F, class... XsH, class... XsL>
struct mapD_impl<F, packer<XsH...>, XsL...> 
    : cons<SROOK_DEDUCED_TYPENAME F::template type<XsH...>::result_type, SROOK_DEDUCED_TYPENAME mapD_impl<F, XsL...>::type> {};

} // namespace detail

template <class F, class... Xs>
struct mapD : detail::mapD_impl<F, Xs...> {};

template <class F, class... Xs>
struct mapD<F, packer<Xs...>> : mapD<F, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, class... Xs>
using mapD_t = SROOK_DEDUCED_TYPENAME mapD<F, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
