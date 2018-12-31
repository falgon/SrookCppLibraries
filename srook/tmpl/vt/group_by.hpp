// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_GROUP_BY_HPP
#define INCLUDED_SROOK_TMPL_VT_GROUP_BY_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/tmpl/vt/cons.hpp>
#include <srook/tmpl/vt/take_whileD.hpp>
#include <srook/tmpl/vt/drop_whileD.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <template <class...> class, class...>
struct group_by;

template <template <class...> class B, class X, class... Xs>
struct group_by<B, X, Xs...> 
    : cons<
        SROOK_DEDUCED_TYPENAME cons<X, SROOK_DEDUCED_TYPENAME take_whileD<bind<B, X>, Xs...>::type>::type,
        SROOK_DEDUCED_TYPENAME group_by<B, SROOK_DEDUCED_TYPENAME drop_whileD<bind<B, X>, X, Xs...>::type>::type
     > {};

template <template <class...> class B>
struct group_by<B>
    : type_constant<packer<>> {};

template <template <class...> class B, class... Xs>
struct group_by<B, packer<Xs...>> : group_by<B, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class B, class... Xs>
using group_by_t = SROOK_DEDUCED_TYPENAME group_by<B, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
