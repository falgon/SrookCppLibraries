// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_MAP_HPP
#define INCLUDED_SROOK_TMPL_VT_MAP_HPP

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

template <template <class...> class, class...>
struct map_impl;

template <template <class...> class F>
struct map_impl<F> : type_constant<packer<>> {};

template <template <class...> class F, class X, class... Xs>
struct map_impl<F, X, Xs...> 
    : cons<SROOK_DEDUCED_TYPENAME F<X>::type, SROOK_DEDUCED_TYPENAME map_impl<F, Xs...>::type> {};

template <template <class...> class F, class... XsH, class... XsL>
struct map_impl<F, packer<XsH...>, XsL...> 
    : cons<SROOK_DEDUCED_TYPENAME F<XsH...>::type, SROOK_DEDUCED_TYPENAME map_impl<F, XsL...>::type> {};

} // namespace detail

template <template <class...> class F, class... Xs>
struct map : detail::map_impl<F, Xs...> {};

template <template <class...> class F, class... Xs>
struct map<F, packer<Xs...>> : map<F, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class F, class... Xs>
using map_t = SROOK_DEDUCED_TYPENAME map<F, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
