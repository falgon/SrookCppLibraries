// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_FOLDL_HPP
#define INCLUDED_SROOK_TMPL_VT_FOLDL_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {
    
template <template <class, class> class, class, class...>
struct foldl_impl;

template <template <class, class> class F, class T>
struct foldl_impl<F, T>
    : type_constant<T> {};

template <template <class, class> class F, class T, class X, class... Xs>
struct foldl_impl<F, T, X, Xs...> 
    : foldl_impl<F, SROOK_DEDUCED_TYPENAME F<T, X>::type, Xs...> {};

} // namespace detail

template <template <class, class> class F, class T, class... Xs>
struct foldl : detail::foldl_impl<F, T, Xs...> {};

template <template <class, class> class F, class T, class... Xs>
struct foldl<F, T, packer<Xs...>> : foldl<F, T, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class, class> class F, class T, class... Xs>
using foldl_t = SROOK_DEDUCED_TYPENAME foldl<F, T, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
