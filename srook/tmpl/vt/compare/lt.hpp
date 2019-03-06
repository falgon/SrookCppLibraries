// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_COMPARISON_LT_HPP
#define INCLUDED_SROOK_TMPL_VT_COMPARISON_LT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/type_traits/bool_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, class> struct lt;

namespace detail {

template <bool, class, class> struct lt_enable_type;

template <class L, class... Ls, class R, class... Rs>
struct lt_enable_type<true, packer<L, Ls...>, packer<R, Rs...>> : type_constant<SROOK_TRUE_TYPE> {};

template <bool b>
struct lt_enable_type<b, packer<>, packer<>> : type_constant<bool_constant<b>> {};

template <bool b, class R, class... Rs>
struct lt_enable_type<b, packer<>, packer<R, Rs...>> : type_constant<bool_constant<b>> {};

template <bool b, class L, class... Ls>
struct lt_enable_type<b, packer<L, Ls...>, packer<>> : type_constant<bool_constant<b>> {};

template <class L, class... Ls, class R, class... Rs>
struct lt_enable_type<false, packer<L, Ls...>, packer<R, Rs...>> : lt<packer<L, Ls...>, packer<R, Rs...>> {};

} // namespace detail

template <class L, class R>
struct lt : type_constant<bool_constant<sizeof(L) < sizeof(R)>> {};

template <class L, class... Ls, class R, class... Rs>
struct lt<packer<L, Ls...>, packer<R, Rs...>> : detail::lt_enable_type<lt<L, R>::type::value, packer<Ls...>, packer<Rs...>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using lt_t = SROOK_DEDUCED_TYPENAME lt<L, R>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool lt_v = lt_t<L, R>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
