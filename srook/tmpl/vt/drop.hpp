// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_DROP_HPP
#define INCLUDED_SROOK_TMPL_VT_DROP_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/partial_tail.hpp>
#include <srook/tmpl/vt/size.hpp>
#include <srook/type_traits/type_constant.hpp>

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool, std::size_t, class... Xs>
struct drop_enable_type 
    : type_constant<packer<>> {};

template <std::size_t x, class... Xs>
struct drop_enable_type<false, x, Xs...> 
    : srook::tmpl::vt::partial_tail<x - 1, Xs...> {};

template <class... Xs>
struct drop_enable_type<false, 0, Xs...> 
    : type_constant<packer<Xs...>> {};

} // namespace detail

template <std::size_t x, class... Xs>
struct drop : detail::drop_enable_type<size<Xs...>::value <= x, x, Xs...> {};

template <std::size_t x, class... Xs>
struct drop<x, packer<Xs...>> : drop<x, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t x, class... Xs>
using drop_t = SROOK_DEDUCED_TYPENAME drop<x, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
