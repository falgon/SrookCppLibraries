// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_POP_BACK_HPP
#define INCLUDED_SROOK_TMPL_VT_POP_BACK_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/at.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

#if 0
template <class... Ts>
struct pop_back 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::PopBack<Ts...>::type::rebind_packer> {};

template <class... Ts>
struct pop_back<packer<Ts...>> : public pop_back<Ts...> {};
#else

namespace detail {

template <class, class...> struct pop_back_impl;
template <std::size_t... x, class... Xs>
struct pop_back_impl<srook::utility::index_sequence<x...>, Xs...> 
    : type_constant<packer<SROOK_DEDUCED_TYPENAME at<x, Xs...>::type...>> {};

template <>
struct pop_back_impl<srook::utility::index_sequence<> >
    : type_constant<packer<> > {};

} // namespace detail

template <class... Ts>
struct pop_back
    : detail::pop_back_impl<SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(Ts) ? sizeof...(Ts) - 1 : 0>::type, Ts...> {};

template <class... Ts>
struct pop_back<packer<Ts...>> : pop_back<Ts...> {};

#endif

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Ts>
using pop_back_t = SROOK_DEDUCED_TYPENAME pop_back<Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook) 

#endif
