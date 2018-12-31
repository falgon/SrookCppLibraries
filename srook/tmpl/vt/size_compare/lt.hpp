// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_COMPARISON_SIZE_LT_HPP
#define INCLUDED_SROOK_TMPL_VT_COMPARISON_SIZE_LT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/size.hpp>
#include <srook/tmpl/vt/compare/lt.hpp>
#include <srook/type_traits/bool_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, class> 
struct size_lt;

namespace detail {

template <class L, class R>
struct size_lt_impl
    : bool_constant<size<L>::value < size<R>::value> {};

} // namespace detail

template <class L, class R>
struct size_lt 
    : lt<L, R>::type {};

template <class... L, class... R>
struct size_lt<packer<L...>, packer<R...>>
    : detail::size_lt_impl<packer<L...>, packer<R...>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using size_lt_t = SROOK_DEDUCED_TYPENAME size_lt<L, R>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool size_lt_v = size_lt<L, R>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
