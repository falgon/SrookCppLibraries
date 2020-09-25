// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_TRANSPOSE_HPP
#define INCLUDED_SROOK_TMPL_VT_TRANSPOSE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/cons.hpp>
#include <srook/tmpl/vt/map.hpp>
#include <srook/tmpl/vt/head.hpp>
#include <srook/tmpl/vt/tail.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/tmpl/vt/erase_packer.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class... Xs> struct transpose_tail : tail<Xs...> {};
template <> struct transpose_tail<> : type_constant<packer<>> {};

template <class... Xs> struct transpose_head : head<Xs...> {};
template <> struct transpose_head<> : type_constant<packer<>> {};

} // namespace detail

template <class...>
struct transpose;

template <class... Xs>
struct transpose 
    : cons<
        SROOK_DEDUCED_TYPENAME erase_packer<SROOK_DEDUCED_TYPENAME map<detail::transpose_head, Xs...>::type>::type, 
        SROOK_DEDUCED_TYPENAME transpose<SROOK_DEDUCED_TYPENAME map<detail::transpose_tail, Xs...>::type>::type
     > {};

template <>
struct transpose<packer<>> : type_constant<packer<>> {};

template <class... Xs>
struct transpose<packer<packer<>, Xs...>> : type_constant<packer<>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Xs>
using transpose_t = SROOK_DEDUCED_TYPENAME transpose<Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
