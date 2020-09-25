// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ZIP_HPP
#define INCLUDED_SROOK_TMPL_VT_ZIP_HPP

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

template <class, class, template <class...> class>
struct zip_impl;

template <template <class...> class Zipper>
struct zip_impl<packer<>, packer<>, Zipper>
    : type_constant<packer<>> {};

template <class X, class... Xs, template <class...> class Zipper>
struct zip_impl<packer<X, Xs...>, packer<>, Zipper>
    : type_constant<packer<>> {};

template <class Y, class... Ys, template <class...> class Zipper>
struct zip_impl<packer<>, packer<Y, Ys...>, Zipper>
    : type_constant<packer<>> {};

template <class X, class... Xs, class Y, class... Ys, template <class...> class Zipper>
struct zip_impl<packer<X, Xs...>, packer<Y, Ys...>, Zipper>
    : cons<Zipper<X, Y>, SROOK_DEDUCED_TYPENAME zip_impl<packer<Xs...>, packer<Ys...>, Zipper>::type> {};

} // namespace detail

template <class, class, template <class...> class = packer>
struct zip;

template <class... L, class... R, template <class> class Zipper>
struct zip<packer<L...>, packer<R...>, Zipper> 
    : detail::zip_impl<packer<L...>, packer<R...>, Zipper> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R, template <class...> class Zipper = packer>
using zip_t = SROOK_DEDUCED_TYPENAME zip<L, R, Zipper>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
