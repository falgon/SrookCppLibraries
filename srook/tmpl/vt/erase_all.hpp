// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ERASE_ALL_HPP
#define INCLUDED_SROOK_TMPL_VT_ERASE_ALL_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1) 

template <class T, class... Ts>
struct erase_all 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::EraseAll<T, Ts...>::type::rebind_packer> {};

template <class T, class... Ts>
struct erase_all<T, packer<Ts...>> : public erase_all<T, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T, class... Ts>
using erase_all_t = SROOK_DEDUCED_TYPENAME erase_all<T, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
