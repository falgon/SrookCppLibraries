// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_FILTERD_HPP
#define INCLUDED_SROOK_TMPL_VT_FILTERD_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/filter.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class...>
struct filterD_impl;

template <class P, class X, class... Xs>
struct filterD_impl<P, X, Xs...>
    : cons<
        SROOK_DEDUCED_TYPENAME conditional<P::template type<X>::value, X, packer<>>::type,
        SROOK_DEDUCED_TYPENAME filterD_impl<P, Xs...>::type
      > {};

template <class P, class... Xs, class... Ys>
struct filterD_impl<P, packer<Xs...>, Ys...>
    : cons<
        SROOK_DEDUCED_TYPENAME conditional<P::template type<Xs...>::value, packer<Xs...>, packer<>>::type,
        SROOK_DEDUCED_TYPENAME filterD_impl<P, Ys...>::type
      > {};

template <class P>
struct filterD_impl<P> : type_constant<packer<>> {};

} // namespace detail

template <class F, class... Xs>
struct filterD 
    : detail::filterd_clean<SROOK_DEDUCED_TYPENAME detail::filterD_impl<F, Xs...>::type> {};

template <class F, class... Xs>
struct filterD<F, packer<Xs...>>
    : filterD<F, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, class... Xs>
using filterD_t = SROOK_DEDUCED_TYPENAME filterD<F, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
