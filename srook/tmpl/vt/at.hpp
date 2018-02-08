// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_AT_HPP
#define INCLUDED_SROOK_TMPL_VT_AT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/preprocessor/detail/loop_comma.hpp>
#include <srook/preprocessor/detail/iterate_def.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

// Non recursive implementation.

namespace detail {

template <std::size_t, class...>
struct at_impl;

template <class T, class... Ts>
struct at_impl<0, T, Ts...> : public type_constant<T> {};

#define CLASS_DECL(N) class T##N
#define LOOP_CNT(N) T##N

#define DEF_AT(N)\
    template <class T, SROOK_PP_LOOP_COMMA(CLASS_DECL, N), class... Ts>\
    struct at_impl<N, T, SROOK_PP_LOOP_COMMA(LOOP_CNT, N), Ts...> : public type_constant<LOOP_CNT(N)> {};

SROOK_PP_ITERATE(DEF_AT, 128)

#undef CLASS_DECL
#undef LOOP_CNT
#undef DEF_AT

} // namespace detail

template <std::size_t x, class... Ts>
struct at : detail::at_impl<x, Ts...> {};

template <std::size_t x, class... Ts>
struct at<x, packer<Ts...>> : at<x, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t t, class... Ts>
using at_t = SROOK_DEDUCED_TYPENAME at<t, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
