// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_OR_HPP
#define INCLUDED_SROOK_TMPL_VT_OR_HPP

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
struct or_impl;

template <class... Xs>
struct or_impl<SROOK_TRUE_TYPE, Xs...> 
    : SROOK_TRUE_TYPE {};

template <class... Xs>
struct or_impl<SROOK_FALSE_TYPE, Xs...> 
    : or_impl<Xs...> {};

template <>
struct or_impl<>
    : SROOK_FALSE_TYPE {};

} // namespace detail

template <class... Ts>
struct or_ : detail::or_impl<Ts...> {};

template <class... Ts>
struct or_<packer<Ts...>> : or_<Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using or_t = SROOK_DEDUCED_TYPENAME or_<Ts...>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class... Ts>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool or_v = or_<Ts...>::type::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
