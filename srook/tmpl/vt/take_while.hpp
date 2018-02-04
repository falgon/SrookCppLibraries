// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_TAKE_WHILE_HPP
#define INCLUDED_SROOK_TMPL_VT_TAKE_WHILE_HPP

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

template <template <class...> class, class...>
struct take_while;

namespace detail {

template <bool, template <class...> class, class...>
struct take_while_impl : type_constant<packer<>> {};

template <template <class...> class F, class X, class... Xs>
struct take_while_impl<true, F, X, Xs...> : cons<X, SROOK_DEDUCED_TYPENAME take_while<F, Xs...>::type> {};

} // namespace detail

template <template <class...> class F>
struct take_while<F> : type_constant<packer<>> {};

template <template <class...> class F, class X, class... Xs>
struct take_while<F, X, Xs...> 
    : detail::take_while_impl<F<X>::value, F, X, Xs...> {}; 

template <template <class...> class F, class... Xs>
struct take_while<F, packer<Xs...>> : take_while<F, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class F, class... Xs>
using take_while_t = SROOK_DEDUCED_TYPENAME take_while<F, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
