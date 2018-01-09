// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_FIRST_HPP
#define INCLUDED_SROOK_TMPL_VT_FIRST_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class... Ts>
struct first : public detail::First<Ts...> {};

template <class... Ts>
struct first<packer<Ts...>> : public first<Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using first_t = SROOK_DEDUCED_TYPENAME first<Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
