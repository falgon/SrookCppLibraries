// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ALL_HPP
#define INCLUDED_SROOK_TMPL_VT_ALL_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/and.hpp>
#include <srook/tmpl/vt/map.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <template <class...> class F, class... Xs>
struct all_impl
    : and_<SROOK_DEDUCED_TYPENAME map<F, Xs...>::type> {};

} // namespace detail

template <template <class...> class F, class... Ts>
struct all : detail::all_impl<F, Ts...> {};

template <template <class...> class F, class... Ts>
struct all<F, packer<Ts...>> : all<F, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class F, class... Ts>
using all_t = SROOK_DEDUCED_TYPENAME all<F, Ts...>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <template <class...> class F, class... Ts>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool allv = all<F, Ts...>::type::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
