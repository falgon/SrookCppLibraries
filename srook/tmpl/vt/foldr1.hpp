// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_FOLDR1_HPP
#define INCLUDED_SROOK_TMPL_VT_FOLDR1_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <template <class, class> class, class...>
struct foldr1_impl;

template <template <class, class> class F, class X, class Y, class... Xs>
struct foldr1_impl<F, X, Y, Xs...>
    : F<X, SROOK_DEDUCED_TYPENAME foldr1_impl<F, Y, Xs...>::type> {};

template <template <class, class> class F, class Init>
struct foldr1_impl<F, Init>
    : type_constant<Init> {};

} // namespace detail

template <template <class, class> class F, class AtLeast1, class... Xs>
struct foldr1 : detail::foldr1_impl<F, AtLeast1, Xs...> {};

template <template <class, class> class F, class AtLeast1, class... Xs>
struct foldr1<F, packer<AtLeast1, Xs...>> : foldr1<F, AtLeast1, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class, class> class F, class AtLeast1, class... Xs>
using foldr1_t = SROOK_DEDUCED_TYPENAME foldr1<F, AtLeast1, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
