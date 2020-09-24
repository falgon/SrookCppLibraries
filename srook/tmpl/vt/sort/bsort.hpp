// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_BSORT_HPP
#define INCLUDED_SROOK_TMPL_VT_BSORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/compare.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/init.hpp>
#include <srook/tmpl/vt/last.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/is_same.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, template <class, class> class = srook::tmpl::vt::lt>
struct bsort;

namespace detail {

template <template <class, class> class, class...>
struct bswap;

template <template <class, class> class Compare, class X>
struct bswap<Compare, X> : type_constant<X> {};

template <template <class, class> class Compare, class X, class Y, class... Xs>
struct bswap<Compare, X, Y, Xs...> {
private:
    typedef SROOK_DEDUCED_TYPENAME conditional<Compare<X, Y>::type::value, X, Y>::type ltype;
    typedef SROOK_DEDUCED_TYPENAME conditional<is_same<ltype, X>::value, Y, X>::type gtype;
public:
    typedef SROOK_DEDUCED_TYPENAME concat<
        ltype, SROOK_DEDUCED_TYPENAME bswap<Compare, gtype, Xs...>::type
    >::type type;
};

} // namespace detail

template <class X, class... Xs, template <class, class> class Compare>
struct bsort<packer<X, Xs...>, Compare>
    : concat<
        SROOK_DEDUCED_TYPENAME bsort<
            SROOK_DEDUCED_TYPENAME init<
                SROOK_DEDUCED_TYPENAME detail::bswap<Compare, X, Xs...>::type
            >::type
        >::type,
        SROOK_DEDUCED_TYPENAME last<
            SROOK_DEDUCED_TYPENAME detail::bswap<Compare, X, Xs...>::type
        >::type
      > {};

template <template <class, class> class Compare>
struct bsort<packer<>, Compare> : type_constant<packer<>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class Xs, template <class, class> class Compare = srook::tmpl::vt::lt>
using bsort_t = SROOK_DEDUCED_TYPENAME bsort<Xs, Compare>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
