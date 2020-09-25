// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_REPLIICATE_HPP
#define INCLUDED_SROOK_TMPL_VT_REPLIICATE_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/erase_packer.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t i, class... Ts>
struct replicate_impl 
    : concat<Ts..., SROOK_DEDUCED_TYPENAME replicate_impl<(i - 1), Ts...>::type> {};

template <class... Ts>
struct replicate_impl<0, Ts...> 
    : type_constant<packer<>> {};

} // namespace detail

template <std::size_t i, class... Ts>
struct replicate 
    : erase_packer<SROOK_DEDUCED_TYPENAME detail::replicate_impl<i, Ts...>::type> {};

template <std::size_t i, class... Ts>
struct replicate<i, packer<Ts...>>
    : replicate<i, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t i, class... Ts>
using replicate_t = SROOK_DEDUCED_TYPENAME replicate<i, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
