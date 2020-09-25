// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_MSORT_HPP
#define INCLUDED_SROOK_TMPL_VT_MSORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/compare.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/take.hpp>
#include <srook/tmpl/vt/drop.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/conditional.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, template <class, class> class = srook::tmpl::vt::lt>
struct msort;

namespace detail {

template <class, class, template <class, class> class>
struct merge;

template <template <class, class> class Compare>
struct merge<packer<>, packer<>, Compare> : type_constant<packer<>> {};

template <class X, class... Xs, template <class, class> class Compare>
struct merge<packer<X, Xs...>, packer<>, Compare> : type_constant<packer<X, Xs...>> {};

template <class Y, class... Ys, template <class, class> class Compare>
struct merge<packer<>, packer<Y, Ys...>, Compare> : type_constant<packer<Y, Ys...>> {};

template <class X, class... Xs, class Y, class... Ys, template <class, class> class Compare>
struct merge<packer<X, Xs...>, packer<Y, Ys...>, Compare> 
    : conditional<
        Compare<X, Y>::type::value,
        SROOK_DEDUCED_TYPENAME concat<X, SROOK_DEDUCED_TYPENAME merge<packer<Xs...>, packer<Y, Ys...>, Compare>::type>::type,
        SROOK_DEDUCED_TYPENAME concat<Y, SROOK_DEDUCED_TYPENAME merge<packer<X, Xs...>, packer<Ys...>, Compare>::type>::type
    > {};

template <class, template <class, class> class>
struct merge_sort;

template <template <class, class> class Compare>
struct merge_sort<packer<>, Compare> : type_constant<packer<>> {};

template <class X, template <class, class> class Compare>
struct merge_sort<packer<X>, Compare> : type_constant<packer<X>> {};

template <class... Xs, template <class, class> class Compare>
struct merge_sort<packer<Xs...>, Compare> 
    : merge<
        SROOK_DEDUCED_TYPENAME merge_sort<SROOK_DEDUCED_TYPENAME take<sizeof...(Xs) / 2, Xs...>::type, Compare>::type,
        SROOK_DEDUCED_TYPENAME merge_sort<SROOK_DEDUCED_TYPENAME drop<sizeof...(Xs) / 2, Xs...>::type, Compare>::type,
        Compare
    > {};

} // namespace detail

template <class... Xs, template <class, class> class Compare>
struct msort<packer<Xs...>, Compare> 
    : detail::merge_sort<packer<Xs...>, Compare> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class Xs, template <class, class> class Compare = srook::tmpl::vt::lt>
using msort_t = SROOK_DEDUCED_TYPENAME msort<Xs, Compare>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
