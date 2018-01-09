// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_SWAP_AT_HPP
#define INCLUDED_SROOK_TMPL_VT_SWAP_AT_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, class, std::size_t>
struct swap_at_left;
template <class, class, std::size_t>
struct swap_at_right;

template <class... L, class... R, std::size_t target>
struct swap_at_left<packer<L...>, packer<R...>, target> 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::SwapAt_L_type<pack<L...>, pack<R...>, target>::type::rebind_packer> {};

template <class... L, class... R, std::size_t target>
struct swap_at_right<packer<L...>, packer<R...>, target> 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::SwapAt_R_type<pack<L...>, pack<R...>, target>::type::rebind_packer> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R, std::size_t target>
using swap_at_left_t = SROOK_DEDUCED_TYPENAME swap_at_left<L, R, target>::type;

template <class L, class R, std::size_t target>
using swap_at_right_t = SROOK_DEDUCED_TYPENAME swap_at_right<L, R, target>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
