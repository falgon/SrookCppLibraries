// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_TAKE_WHILED_HPP
#define INCLUDED_SROOK_TMPL_VT_TAKE_WHILED_HPP

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
struct take_whileD;

namespace detail {

template <bool, class, class...>
struct take_whileD_impl : type_constant<packer<>> {};

template <class F, class X, class... Xs>
struct take_whileD_impl<true, F, X, Xs...> : cons<X, SROOK_DEDUCED_TYPENAME take_whileD<F, Xs...>::type> {};

} // namespace detail

template <class F>
struct take_whileD<F> : type_constant<packer<>> {};

template <class F, class X, class... Xs>
struct take_whileD<F, X, Xs...> 
    : detail::take_whileD_impl<F::template type<X>::type::value, F, X, Xs...> {}; 

template <class F, class... Xs>
struct take_whileD<F, packer<Xs...>> : take_whileD<F, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, class... Xs>
using take_whileD_t = SROOK_DEDUCED_TYPENAME take_whileD<F, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
