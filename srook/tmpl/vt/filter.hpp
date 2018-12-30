// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_FILTER_HPP
#define INCLUDED_SROOK_TMPL_VT_FILTER_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/cons.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/erase_packer.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/conditional.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <template <class...> class, class...>
struct filter_impl;

template <template <class...> class P, class X, class... Xs>
struct filter_impl<P, X, Xs...>
    : cons<
        SROOK_DEDUCED_TYPENAME conditional<P<X>::value, X, packer<>>::type,
        SROOK_DEDUCED_TYPENAME filter_impl<P, Xs...>::type
      > {};

template <template <class...> class P, class... Xs, class... Ys>
struct filter_impl<P, packer<Xs...>, Ys...>
    : cons<
        SROOK_DEDUCED_TYPENAME conditional<P<Xs...>::value, packer<Xs...>, packer<>>::type,
        SROOK_DEDUCED_TYPENAME filter_impl<P, Ys...>::type
      > {};

template <template <class...> class P>
struct filter_impl<P> : type_constant<packer<>> {};

template <class...> struct filterd_clean;
template <class X, class... Xs>
struct filterd_clean<packer<X, Xs...>> 
    : cons<X, SROOK_DEDUCED_TYPENAME filterd_clean<packer<Xs...>>::type> {};
template <class... Xs>
struct filterd_clean<packer<packer<>, Xs...>>
    : filterd_clean<packer<Xs...>> {};
template <> 
struct filterd_clean<packer<>> 
    : type_constant<packer<>> {};

} // namespace detail

template <template <class...> class F, class... Xs>
struct filter 
    : detail::filterd_clean<SROOK_DEDUCED_TYPENAME detail::filter_impl<F, Xs...>::type> {};

template <template <class...> class F, class... Xs>
struct filter<F, packer<Xs...>>
    : filter<F, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class F, class... Xs>
using filter_t = SROOK_DEDUCED_TYPENAME filter<F, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
