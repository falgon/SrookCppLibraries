// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_AND_HPP
#define INCLUDED_SROOK_TMPL_VT_AND_HPP

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

template <class...>
struct and_impl;

template <class... Xs>
struct and_impl<SROOK_TRUE_TYPE, Xs...> 
    : and_impl<Xs...> {};

template <class... Xs>
struct and_impl<SROOK_FALSE_TYPE, Xs...> 
    : SROOK_FALSE_TYPE {};

template <>
struct and_impl<>
    : SROOK_TRUE_TYPE {};

} // namespace detail

template <class... Ts>
struct and_ : detail::and_impl<Ts...> {};

template <class... Ts>
struct and_<packer<Ts...>> : and_<Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using and_t = SROOK_DEDUCED_TYPENAME and_<Ts...>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class... Ts>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool and_v = and_<Ts...>::type::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
