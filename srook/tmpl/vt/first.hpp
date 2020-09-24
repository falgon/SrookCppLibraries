// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_FIRST_HPP
#define INCLUDED_SROOK_TMPL_VT_FIRST_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class...>
struct first_impl;

template <class H, class... Ts>
struct first_impl<H, Ts...> : type_constant<H> {};

} // namespace detail

template <class... Ts>
struct first : public detail::first_impl<Ts...> {};

template <class... Ts>
struct first<packer<Ts...>> : public first<Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using first_t = SROOK_DEDUCED_TYPENAME first<Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
