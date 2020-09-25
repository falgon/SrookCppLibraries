// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ERASE_AT_HPP
#define INCLUDED_SROOK_TMPL_VT_ERASE_AT_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/cons.hpp>
#include <srook/tmpl/vt/head.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1) 

namespace detail {

template <std::size_t x, bool = true, class...>
struct erase_at_impl;

template <std::size_t x, class X, class... Xs>
struct erase_at_impl<x, true, X, Xs...> 
    : cons<X, SROOK_DEDUCED_TYPENAME erase_at_impl<x - 1, bool(x - 1), Xs...>::type> {};

template <class X, class... Xs>
struct erase_at_impl<0, false, X, Xs...> : type_constant<packer<Xs...>> {};

} // namespace detail

template <std::size_t x, class... Xs>
struct erase_at : detail::erase_at_impl<x, bool(x), Xs...> {};

template <std::size_t x, class... Xs>
struct erase_at<x, packer<Xs...>> : erase_at<x, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t x, class... Xs>
using erase_at_t = SROOK_DEDUCED_TYPENAME erase_at<x, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
