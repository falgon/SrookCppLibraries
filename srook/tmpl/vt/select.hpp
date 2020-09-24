// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_SELECT_HPP
#define INCLUDED_SROOK_TMPL_VT_SELECT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/move_head.hpp>
#include <srook/tmpl/vt/tail.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class... Xs>
struct select_cons : type_constant<packer<Xs...>> {};

template <class, class...>
struct select_impl;

template <std::size_t... x, class... Xs>
struct select_impl<index_sequence<x...>, Xs...>
    : select_cons<SROOK_DEDUCED_TYPENAME move_head<x, Xs...>::type...> {};

} // namespace detail

template <class... Xs>
struct select 
    : detail::select_impl<SROOK_DEDUCED_TYPENAME make_index_sequence_type<(sizeof...(Xs) ? sizeof...(Xs) : 0)>::type, Xs...> {};

template <class... Xs>
struct select<packer<Xs...>> : select<Xs...> {};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
