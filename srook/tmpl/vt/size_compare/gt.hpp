// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_COMPARISON_SIZE_GT_HPP
#define INCLUDED_SROOK_TMPL_VT_COMPARISON_SIZE_GT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/size_compare/leq.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, class> 
struct size_gt;

namespace detail {

template <class L, class R>
struct size_gt_impl
    : type_traits::detail::Lnot<size_leq<L, R>> {};

} // namespace detail

template <class L, class R>
struct size_gt 
    : detail::size_gt_impl<L, R> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using size_gt_t = SROOK_DEDUCED_TYPENAME size_gt<L, R>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool size_gt_v = size_gt<L, R>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
