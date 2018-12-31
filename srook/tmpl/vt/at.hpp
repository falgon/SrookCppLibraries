// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_AT_HPP
#define INCLUDED_SROOK_TMPL_VT_AT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/add_pointer.hpp>
#include <srook/utility/index_sequence.hpp>
#include <srook/utility/void_t.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class>
struct at_impl;

template <std::size_t... x>
struct at_impl<srook::utility::index_sequence<x...> > {
    template <class T>
    static T get(SROOK_DEDUCED_TYPENAME voider<integral_constant<std::size_t, x> >::type*..., T*, ...);
};

} // namespace detail

template <std::size_t x, class... Ts>
struct at 
    : type_constant<
        SROOK_DECLTYPE(
            detail::at_impl<
                SROOK_DEDUCED_TYPENAME srook::utility::make_index_sequence_type<x>::type
            >::get(SROOK_DEDUCED_TYPENAME add_pointer<Ts>::type()...)
        )
    > {};

template <std::size_t x, class... Ts>
struct at<x, packer<Ts...>> : at<x, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t t, class... Ts>
using at_t = SROOK_DEDUCED_TYPENAME at<t, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
