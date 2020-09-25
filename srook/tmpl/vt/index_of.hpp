// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_INDEX_OF_HPP
#define INCLUDED_SROOK_TMPL_VT_INDEX_OF_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class... Ts>
struct index_of : public detail::IndexOf<T, Ts...> {};

template <class T, class... Ts>
struct index_of<T, packer<Ts...>> : public index_of<T, Ts...> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class... Ts>
SROOK_CONSTEXPR int index_of_v = index_of<T, Ts...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
