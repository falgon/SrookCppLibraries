// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ANY_HPP
#define INCLUDED_SROOK_TMPL_VT_ANY_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/true_false_type.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <template <class> class, class...>
struct any_impl;

template <template <class> class F, class X, class... Xs>
struct any_impl<F, X, Xs...> 
    : conditional<F<X>::value, SROOK_TRUE_TYPE, SROOK_DEDUCED_TYPENAME any_impl<F, Xs...>::type> {};

template <template <class> class F>
struct any_impl<F>
    : type_constant<SROOK_FALSE_TYPE> {};

} // namespace detail

template <template <class> class F, class... Ts>
struct any : detail::any_impl<F, Ts...> {};

template <template <class> class F, class... Ts>
struct any<F, packer<Ts...>> : any<F, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class> class F, class... Ts>
using any_t = SROOK_DEDUCED_TYPENAME any<F, Ts...>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <template <class> class F, class... Ts>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool any_v = any<F, Ts...>::type::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
