// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_REPLACE_ALL_LIKE_HPP
#define INCLUDED_SROOK_TMPL_VT_REPLACE_ALL_LIKE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/conditional.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <template <class...> class, class, class...>
struct replace_all_like_impl;

template <template <class...> class Likea, class R>
struct replace_all_like_impl<Likea, R> : public type_constant<packer<>> {};

template <template <class...> class Likea, class R, class Head, class... Ts>
struct replace_all_like_impl<Likea, R, Head, Ts...> 
    : public concat<
        SROOK_DEDUCED_TYPENAME conditional<Likea<Head>::value, R, Head>::type, 
        SROOK_DEDUCED_TYPENAME replace_all_like_impl<Likea, R, Ts...>::type
    > {};

template <template <class...> class Likea, class R, class... Elem, class... Ts>
struct replace_all_like_impl<Likea, R, packer<Elem...>, Ts...>
    : public concat<
        SROOK_DEDUCED_TYPENAME conditional<Likea<Elem...>::value, R, packer<Elem...>>::type,
        SROOK_DEDUCED_TYPENAME replace_all_like_impl<Likea, R, Ts...>::type
    > {};

} // namespace detail

template <template <class...> class Likea, class R, class... Ts>
struct replace_all_like : public detail::replace_all_like_impl<Likea, R, Ts...> {};

template <template <class...> class Likea, class R, class... Ts>
struct replace_all_like<Likea, R, packer<Ts...>> : public detail::replace_all_like_impl<Likea, R, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class Likea, class R, class... Ts>
using replace_all_like_t = SROOK_DEDUCED_TYPENAME replace_all_like<Likea, R, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
