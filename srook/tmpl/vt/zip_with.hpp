// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ZIP_WITH_HPP
#define INCLUDED_SROOK_TMPL_VT_ZIP_WITH_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/cons.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <template <class, class> class, class, class>
struct zip_with_impl;

template <template <class, class> class Fn, class X, class... Xs>
struct zip_with_impl<Fn, packer<X, Xs...>, packer<>>
    : type_constant<packer<>> {};

template <template <class, class> class Fn, class Y, class... Ys>
struct zip_with_impl<Fn, packer<>, packer<Y, Ys...>>
    : type_constant<packer<>> {};

template <template <class, class> class Fn>
struct zip_with_impl<Fn, packer<>, packer<>>
    : type_constant<packer<>> {};

template <template <class, class> class Fn, class X, class... Xs, class Y, class... Ys>
struct zip_with_impl<Fn, packer<X, Xs...>, packer<Y, Ys...>>
    : cons<SROOK_DEDUCED_TYPENAME Fn<X, Y>::type, SROOK_DEDUCED_TYPENAME zip_with_impl<Fn, packer<Xs...>, packer<Ys...>>::type> {};

} // namespace detail

template <template <class, class> class Fn, class L, class... R>
struct zip_with : detail::zip_with_impl<Fn, L, packer<R...>> {};

template <template <class, class> class Fn, class L, class... R>
struct zip_with<Fn, L, packer<R...>> : detail::zip_with_impl<Fn, L, packer<R...>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class, class> class Fn, class L, class... R>
using zip_with_t = SROOK_DEDUCED_TYPENAME zip_with<Fn, L, R...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
