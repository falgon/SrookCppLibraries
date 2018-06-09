// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_TAKE_HPP
#define INCLUDED_SROOK_TMPL_VT_TAKE_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/partial_head.hpp>
#include <srook/tmpl/vt/size.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/conditional.hpp>

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool, std::size_t, class... Xs>
struct take_enable_type : type_constant<packer<Xs...>> {};

template <std::size_t x, class... Xs>
struct take_enable_type<false, x, Xs...> : srook::tmpl::vt::partial_head<x, Xs...> {};

template <class... Xs>
struct take_enable_type<false, 0, Xs...> : type_constant<packer<>> {};

} // namespace detail

template <std::size_t x, class... Xs>
struct take : detail::take_enable_type<size<Xs...>::value < x, x, Xs...> {};

template <std::size_t x, class... Xs>
struct take<x, packer<Xs...>> : take<x, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t x, class... Xs>
using take_t = SROOK_DEDUCED_TYPENAME take<x, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
