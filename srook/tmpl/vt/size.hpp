// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_SIZE_HPP
#define INCLUDED_SROOK_TMPL_VT_SIZE_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class...>
struct size;

template <>
struct size<> : integral_constant<std::size_t, 0> {};

template <class T, class... Ts>
struct size<T, Ts...> : public detail::Size<T, Ts...> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class... Ts>
SROOK_CONSTEXPR int size_v = size<Ts...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
