// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_PARTIAL_HEAD_HPP
#define INCLUDED_SROOK_TMPL_VT_PARTIAL_HEAD_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/utility/index_sequence.hpp>
#include <srook/tmpl/vt/at.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

#if 0
template <std::size_t k, class... Ts>
struct partial_head 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::PartialHead<k, Ts...>::type::rebind_packer> {};

template <std::size_t k, class... Ts>
struct partial_head<k, packer<Ts...>> : public partial_head<k, Ts...> {};
#else

namespace detail {

template <class, class...> struct partial_head;

template <std::size_t... x, class... Ts>
struct partial_head<srook::utility::index_sequence<x...>, Ts...>
    : type_constant<packer<SROOK_DEDUCED_TYPENAME at<x, Ts...>::type...> > {};

template <class... Ts>
struct partial_head<srook::utility::index_sequence<>, Ts...>
    : type_constant<packer<Ts...>> {};

} // namespace detail

template <std::size_t k, class... Ts>
struct partial_head 
    : detail::partial_head<SROOK_DEDUCED_TYPENAME make_index_sequence_type<k>::type, Ts...> {};

template <std::size_t k, class... Ts>
struct partial_head<k, packer<Ts...>> 
    : partial_head<k, Ts...> {};

#endif

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t k, class... Ts>
using partial_head_t = SROOK_DEDUCED_TYPENAME partial_head<k, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
