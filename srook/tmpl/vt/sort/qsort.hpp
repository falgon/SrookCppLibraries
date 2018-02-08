// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_QSORT_HPP
#define INCLUDED_SROOK_TMPL_VT_QSORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/tmpl/vt/compare.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/erase.hpp>
#include <srook/tmpl/vt/filterD.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct qsort_bind_proxy : type_constant<T> {};

template <template <class, class> class Comp>
struct qsort_compare_proxy {
    template <class L, class R>
    struct type 
        : Comp<L, R>::type {};
};

template <template <class, class> class Comp>
struct qsort_compare_not_proxy {
    template <class L, class R>
    struct type 
        : type_traits::detail::Lnot<SROOK_DEDUCED_TYPENAME Comp<L, R>::type> {};
};

} // namespace detail

template <class, template <class, class> class = srook::tmpl::vt::lt>
struct qsort;

template <class X, class... Xs, template <class, class> class Compare>
struct qsort<packer<X, Xs...>, Compare> 
    : concat<
            SROOK_DEDUCED_TYPENAME qsort<
                SROOK_DEDUCED_TYPENAME filterD<bind<Compare, srook::tmpl::vt::placeholders::_1, X>, Xs...>::type,
                Compare
            >::type,
            SROOK_DEDUCED_TYPENAME cons<
                X,
                SROOK_DEDUCED_TYPENAME qsort<
                    SROOK_DEDUCED_TYPENAME filterD<bind<detail::qsort_compare_not_proxy<Compare>::template type, srook::tmpl::vt::placeholders::_1, X>, Xs...>::type,
                    Compare
                >::type
           >::type
     > {};

template <template <class, class> class Compare>
struct qsort<packer<>, Compare> : type_constant<packer<>> {};

template <class X, class... Xs>
struct qsort<packer<X, Xs...>, srook::tmpl::vt::lt> 
    : qsort<packer<X, Xs...>, detail::qsort_compare_proxy<srook::tmpl::vt::lt>::template type> {};

template <class X, class... Xs>
struct qsort<packer<X, Xs...>, srook::tmpl::vt::gt>
    : qsort<packer<X, Xs...>, detail::qsort_compare_proxy<srook::tmpl::vt::gt>::template type> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class Xs, template <class, class> class Compare = srook::tmpl::vt::lt>
using qsort_t = SROOK_DEDUCED_TYPENAME qsort<Xs, Compare>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
