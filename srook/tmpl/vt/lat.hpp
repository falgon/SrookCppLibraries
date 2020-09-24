// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_LAT_HPP
#define INCLUDED_SROOK_TMPL_VT_LAT_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <std::size_t t, class... Ts>
struct lat : public detail::At<t, Ts...> {};

template <std::size_t t, class... Ts>
struct lat<t, packer<Ts...>> : public detail::At<t, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t t, class... Ts>
using lat_t = SROOK_DEDUCED_TYPENAME lat<t, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
