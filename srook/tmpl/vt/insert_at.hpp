// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_INSERT_AT_HPP
#define INCLUDED_SROOK_TMPL_VT_INSERT_AT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/partial_tail.hpp>
#include <srook/tmpl/vt/at.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

#if 0
namespace detail {

template <std::size_t, bool, class, class...>
struct insert_at_impl;

template <std::size_t x, class T, class X, class... Xs>
struct insert_at_impl<x, true, T, X, Xs...>
    : concat<X, SROOK_DEDUCED_TYPENAME insert_at_impl<x - 1, bool(x - 1), T, Xs...>::type> {};

template <class T, class... Xs>
struct insert_at_impl<0, false, T, Xs...>
    : type_constant<packer<T, Xs...>> {};

} // namespace detail

template <std::size_t x, class T, class... Xs>
struct insert_at 
    : conditional<
        (x < sizeof...(Xs)), 
        detail::insert_at_impl<x, bool(x), T, Xs...>,
        type_constant<packer<Xs..., T>>
     >::type {};

template <std::size_t x, class T, class... Xs>
struct insert_at<x, T, packer<Xs...>> : insert_at<x, T, Xs...> {};
#else

namespace detail {

template <class, std::size_t, class, class...> struct insert_at;

template <class T, std::size_t t, std::size_t... x, class... Xs>
struct insert_at<T, t, srook::utility::index_sequence<x...>, Xs...> 
    : concat<SROOK_DEDUCED_TYPENAME concat<SROOK_DEDUCED_TYPENAME at<x, Xs...>::type..., T>::type, SROOK_DEDUCED_TYPENAME srook::tmpl::vt::partial_tail<t - 1, Xs...>::type> {};

template <class T, class... Xs>
struct insert_at<T, 0, srook::utility::index_sequence<>, Xs...>
    : concat<T, Xs...> {};

} // namespace detail

template <std::size_t x, class T, class... Xs>
struct insert_at 
    : detail::insert_at<T, x, SROOK_DEDUCED_TYPENAME make_index_sequence_type<x>::type, Xs...> {};

template <std::size_t x, class T, class... Xs>
struct insert_at<x, T, packer<Xs...>> : insert_at<x, T, Xs...> {};

#endif

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t x, class T, class... Xs>
using insert_at_t = SROOK_DEDUCED_TYPENAME insert_at<x, T, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
