// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_PARTIAL_HEAD_HPP
#define INCLUDED_SROOK_TMPL_VT_PARTIAL_HEAD_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <std::size_t k, class... Ts>
struct partial_head 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::PartialHead<k, Ts...>::type::rebind_packer> {};

template <std::size_t k, class... Ts>
struct partial_head<k, packer<Ts...>> : public partial_head<k, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t k, class... Ts>
using partial_head_t = SROOK_DEDUCED_TYPENAME partial_head<k, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
