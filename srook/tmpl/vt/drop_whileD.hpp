// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_DROP_WHILED_HPP
#define INCLUDED_SROOK_TMPL_VT_DROP_WHILED_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/cons.hpp>
#include <srook/type_traits/type_constant.hpp>

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, class...>
struct drop_whileD;

namespace detail {

template <bool, class, class... Xs>
struct drop_whileD_impl : type_constant<packer<Xs...>> {};

template <class F, class X, class... Xs>
struct drop_whileD_impl<true, F, X, Xs...> : drop_whileD<F, Xs...> {};

} // namespace detail

template <class, class...>
struct drop_whileD;

template <class F>
struct drop_whileD<F> : type_constant<packer<>> {};

template <class F, class X, class... Xs>
struct drop_whileD<F, X, Xs...> 
    : detail::drop_whileD_impl<F::template type<X>::value, F, X, Xs...> {}; 

template <class F, class... Xs>
struct drop_whileD<F, packer<Xs...>> : drop_whileD<F, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, class... Xs>
using drop_whileD_t = SROOK_DEDUCED_TYPENAME drop_whileD<F, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
