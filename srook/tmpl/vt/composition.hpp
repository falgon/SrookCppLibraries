// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_COMPOSITION_HPP
#define INCLUDED_SROOK_TMPL_VT_COMPOSITION_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/tt_proxy.hpp>
#include <srook/tmpl/vt/reverse.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, template <class...> class...>
struct generate_impl;

template <class T, template <class...> class F, template <class...> class... Fs>
struct generate_impl<T, F, Fs...>
    : generate_impl<SROOK_DEDUCED_TYPENAME F<T>::type, Fs...> {};

template <class T>
struct generate_impl<T> 
    : type_constant<T> {};

/*
template <template <class...> class... Fs>
struct composition_impl {
    template <class T>
    struct generate : generate_impl<T, Fs...> {};
};*/

template <class>
struct composition_impl;

template <class... TTP>
struct composition_impl<tmpl::vt::packer<TTP...>> {
    template <class T>
    struct generate 
        : generate_impl<T, TTP::template ftype...> {};
};

} // namespace detail

template <template <class...> class... Xs>
struct composition 
    : detail::composition_impl<SROOK_DEDUCED_TYPENAME tmpl::vt::reverse<tt_proxy<Xs>...>::type> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class... Xs>
using composition_generate = SROOK_DEDUCED_TYPENAME composition<Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
