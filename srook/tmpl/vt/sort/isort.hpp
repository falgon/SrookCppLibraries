// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ISORT_HPP
#define INCLUDED_SROOK_TMPL_VT_ISORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/compare.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/conditional.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, template <class, class> class = srook::tmpl::vt::lt>
struct isort;

namespace detail {

template <template <class, class> class, class, class>
struct insert;

template <template <class, class> class Op, class X>
struct insert<Op, X, packer<>> : type_constant<packer<X>> {};

template <template <class, class> class Op, class X, class Y, class... Ys>
struct insert<Op, X, packer<Y, Ys...>> 
    : conditional<
        Op<X, Y>::type::value, 
        packer<X, Y, Ys...>,
        SROOK_DEDUCED_TYPENAME concat<Y, SROOK_DEDUCED_TYPENAME insert<Op, X, packer<Ys...>>::type>::type
    > {};

template <template <class, class> class, class>
struct insert_sort;

template <template <class, class> class Op>
struct insert_sort<Op, packer<>> : type_constant<packer<>> {};

template <template <class, class> class Op, class X, class... Xs>
struct insert_sort<Op, packer<X, Xs...>> 
    : insert<Op, X, SROOK_DEDUCED_TYPENAME insert_sort<Op, packer<Xs...>>::type> {};

} // namespace detail

template <class... Xs, template <class, class> class Compare>
struct isort<packer<Xs...>, Compare> 
    : detail::insert_sort<Compare, packer<Xs...>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class Xs, template <class, class> class Compare = srook::tmpl::vt::lt>
using isort_t = SROOK_DEDUCED_TYPENAME isort<Xs, Compare>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
