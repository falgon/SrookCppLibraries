// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ERASE_PACKER_HPP
#define INCLUDED_SROOK_TMPL_VT_ERASE_PACKER_HPP

#ifndef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/null.hpp>
#include <srook/tmpl/vt/erase_if.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class... Xs>
struct erase_packer_bind : null<Xs...>::type {};

} // namespace detail

template <class... Xs>
struct erase_packer : erase_if<detail::erase_packer_bind, Xs...> {};

template <class... Xs>
struct erase_packer<packer<Xs...>> : erase_packer<Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Xs>
using erase_packer_t = SROOK_DEDUCED_TYPENAME erase_packer<Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
