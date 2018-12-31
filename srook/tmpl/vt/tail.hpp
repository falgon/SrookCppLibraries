// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_TAIL_HPP
#define INCLUDED_SROOK_TMPL_VT_TAIL_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/utility/index_sequence.hpp>
#include <srook/utility/void_t.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

#if 0
template <class...>
struct tail;

template <class X, class... Xs>
struct tail<X, Xs...> : type_constant<packer<Xs...>> {};

template <class... Xs>
struct tail<packer<Xs...>> : tail<Xs...> {};
#else

namespace detail {

template <class> struct tail_impl;

template <std::size_t... x>
struct tail_impl<srook::utility::index_sequence<x...> > {
    template <class T>
    static T get(SROOK_DEDUCED_TYPENAME voider<integral_constant<std::size_t, x> >::type*..., T*);
};

template <>
struct tail_impl<srook::utility::index_sequence<> > {
    static packer<> get();
};

} // namespace detail

template <class... Ts>
struct tail
    : type_constant<
        SROOK_DECLTYPE(
            detail::tail_impl<
                SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(Ts) ? sizeof...(Ts) - 1 : 0>::type
            >::get(SROOK_DEDUCED_TYPENAME add_pointer<Ts>::type()...)
        )
      > {};

template <class... Ts>
struct tail<packer<Ts...>> : tail<Ts...> {};

#endif

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Xs>
using tail_t = SROOK_DEDUCED_TYPENAME tail<Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
