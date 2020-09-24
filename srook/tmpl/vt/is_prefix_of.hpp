// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_IS_PREFIX_OF_HPP
#define INCLUDED_SROOK_TMPL_VT_IS_PREFIX_OF_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/type_traits/bool_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class>
struct is_prefix_of_impl;

template <class X, class... Xs, class... Ys>
struct is_prefix_of_impl<packer<X, Xs...>, packer<X, Ys...>>
    : is_prefix_of_impl<packer<Xs...>, packer<Ys...>> {};

template <class... Ys>
struct is_prefix_of_impl<packer<>, packer<Ys...>>
    : bool_constant<true> {};

template <class X, class... Xs>
struct is_prefix_of_impl<packer<X, Xs...>, packer<>>
    : bool_constant<false> {};

template <class X, class... Xs, class Y, class... Ys>
struct is_prefix_of_impl<packer<X, Xs...>, packer<Y, Ys...>>
    : bool_constant<false> {};

} // namespace detail

template <class, class...>
struct is_prefix_of;

template <class... Xs, class... Ys>
struct is_prefix_of<packer<Xs...>, packer<Ys...>> 
    : detail::is_prefix_of_impl<packer<Xs...>, packer<Ys...>> {};

template <class... Xs, class... Ys>
struct is_prefix_of<packer<Xs...>, Ys...>
    : detail::is_prefix_of_impl<packer<Xs...>, packer<Ys...>> {};
    
#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class... R>
using is_prefix_of_t = SROOK_DEDUCED_TYPENAME is_prefix_of<L, R...>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class... R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_prefix_of_v = is_prefix_of<L, R...>::type::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
