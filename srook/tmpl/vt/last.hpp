// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_LAST_HPP
#define INCLUDED_SROOK_TMPL_VT_LAST_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class... Ts>
struct last : public detail::Last<Ts...> {};

template <class... Ts>
struct last<packer<Ts...>> : public last<Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using last_t = SROOK_DEDUCED_TYPENAME last<Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
