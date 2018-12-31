// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_TAILS_HPP
#define INCLUDED_SROOK_TMPL_VT_TAILS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/pop_front.hpp>
#include <srook/tmpl/vt/cons.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class>
struct tails_impl;

template <class... Ts>
struct tails_impl<packer<Ts...>>
    : cons<packer<Ts...>, SROOK_DEDUCED_TYPENAME tails_impl<SROOK_DEDUCED_TYPENAME pop_front<Ts...>::type>::type> {};

template <>
struct tails_impl<packer<>>
    : type_constant<packer<>> {};

} // namespace detail

template <class... Ts>
struct tails 
    : detail::tails_impl<packer<Ts...>> {};

template <class... Ts>
struct tails<packer<Ts...>> : detail::tails_impl<packer<Ts...>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using tails_t = SROOK_DEDUCED_TYPENAME tails<Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
