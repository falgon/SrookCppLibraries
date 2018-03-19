// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_SET_PRODUCT_HPP
#define INCLUDED_SROOK_TMPL_VT_SET_PRODUCT_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/unique.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/filterD.hpp>
#include <srook/tmpl/vt/size_max.hpp>
#include <srook/tmpl/vt/size_min.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/type_constant.hpp>

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class>
struct set_product_impl;

template <class X, class... Xs, class R>
struct set_product_impl<packer<X, Xs...>, R>
    : concat<
        SROOK_DEDUCED_TYPENAME filterD<bind<is_same, X>, R>::type,
        SROOK_DEDUCED_TYPENAME set_product_impl<packer<Xs...>, R>::type
    > {};

template <class... Xs>
struct set_product_impl<packer<>, packer<Xs...>> : type_constant<packer<>> {};

} // namespace detail

template <class L, class R>
struct set_product 
    : detail::set_product_impl<
        SROOK_DEDUCED_TYPENAME unique<SROOK_DEDUCED_TYPENAME size_min<L, R>::type>::type, 
        SROOK_DEDUCED_TYPENAME unique<SROOK_DEDUCED_TYPENAME size_max<L, R>::type>::type
    > {}; 

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using set_product_t = SROOK_DEDUCED_TYPENAME set_product<L, R>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
