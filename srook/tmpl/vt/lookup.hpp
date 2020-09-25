// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_LOOKUP_HPP
#define INCLUDED_SROOK_TMPL_VT_LOOKUP_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/defines/map.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_same.hpp>
#include <utility>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class>
struct lookup_impl;

template <class T>
struct lookup_impl<T, packer<>>
    : type_constant<SROOK_NULLOPT_T> {};

template <class T, class X, class... Xs>
struct lookup_impl<T, packer<X, Xs...>>
    : conditional<
        is_same<SROOK_DEDUCED_TYPENAME defines::map_types<X>::key_type, T>::value, 
        SROOK_DEDUCED_TYPENAME defines::map_types<X>::mapped_type,
        SROOK_DEDUCED_TYPENAME lookup_impl<T, packer<Xs...>>::type
    > {};

} // namespace detail

template <class, class>
struct lookup;

template <class T, class... Ts>
struct lookup<T, packer<Ts...>>
    : detail::lookup_impl<T, packer<Ts...>> {
    SROOK_STATIC_ASSERT(type_traits::detail::Land<defines::is_map<Ts>...>::value, "Given types are not map");
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T, class M>
using lookup_t = SROOK_DEDUCED_TYPENAME lookup<T, M>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
