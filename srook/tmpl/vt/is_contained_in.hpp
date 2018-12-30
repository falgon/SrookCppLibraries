// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_IS_CONTAINED_IN_HPP
#define INCLUDED_SROOK_TMPL_VT_IS_CONTAINED_IN_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class... Ts>
struct is_contained_in : public detail::is_contained_in<T, Ts...> {};

template <class T, class... Ts>
struct is_contained_in<T, packer<Ts...>> : public is_contained_in<T, Ts...> {};

#if SROOK_CPP_VARIADIC_TEMPLATES
template <class T, class... Ts>
SROOK_CONSTEXPR bool is_contained_in_v = is_contained_in<T, Ts...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
