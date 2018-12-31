// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_POP_FRONT_HPP
#define INCLUDED_SROOK_TMPL_VT_POP_FRONT_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/partial_tail.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

#if 0
template <class... Ts>
struct pop_front 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::PopFront<Ts...>::type::rebind_packer> {};

template <class... Ts>
struct pop_front<packer<Ts...>> : public pop_front<Ts...> {};
#else

template <class... Ts>
struct pop_front : partial_tail<0, Ts...> {};

#endif

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using pop_front_t = SROOK_DEDUCED_TYPENAME pop_front<Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook) 

#endif
