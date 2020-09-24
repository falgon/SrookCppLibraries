// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_CONCAT_HPP
#define INCLUDED_SROOK_TMPL_VT_CONCAT_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class... Ts>
struct concat 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::Concat<Ts...>::type::rebind_packer> {};

template <class... L, class... R>
struct concat<packer<L...>, R...> : public concat<L..., R...> {};

template <class... L, class... R>
struct concat<packer<L...>, packer<R...>> : public concat<L..., R...> {};

template <class T, class... Ts>
struct concat<T, packer<Ts...>> : public concat<T, Ts...> {};

template <>
struct concat<> : type_constant<packer<>> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using concat_t = SROOK_DEDUCED_TYPENAME concat<Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
