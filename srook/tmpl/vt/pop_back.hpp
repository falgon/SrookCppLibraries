// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_POP_BACK_HPP
#define INCLUDED_SROOK_TMPL_VT_POP_BACK_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class... Ts>
struct pop_back 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::PopBack<Ts...>::type::rebind_packer> {};

template <class... Ts>
struct pop_back<packer<Ts...>> : public pop_back<Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using pop_back_t = SROOK_DEDUCED_TYPENAME pop_back<Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook) 

#endif
