// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_SWAP_AT_SPECIFIED_HPP
#define INCLUDED_SROOK_TMPL_VT_SWAP_AT_SPECIFIED_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class, std::size_t, class, std::size_t>
struct swap_at_specified_left;
template <class, std::size_t, class, std::size_t>
struct swap_at_specified_right;

template <class... L, std::size_t left_target, class... R, std::size_t right_target>
struct swap_at_specified_left<packer<L...>, left_target, packer<R...>, right_target> 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::SwapAt_Specified_L_type<pack<L...>, left_target, pack<R...>, right_target>::type::rebind_packer> {};

template <class... L, std::size_t left_target, class... R, std::size_t right_target>
struct swap_at_specified_right<packer<L...>, left_target, packer<R...>, right_target> 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::SwapAt_Specified_R_type<pack<L...>, left_target, pack<R...>, right_target>::type::rebind_packer> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, std::size_t left_target, class R, std::size_t right_target>
using swap_at_specified_left_t = SROOK_DEDUCED_TYPENAME swap_at_specified_left<L, left_target, R, right_target>::type;

template <class L, std::size_t left_target, class R, std::size_t right_target>
using swap_at_specified_right_t = SROOK_DEDUCED_TYPENAME swap_at_specified_right<L, left_target, R, right_target>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
