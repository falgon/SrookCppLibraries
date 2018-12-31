// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_APPLY_HPP
#define INCLUDED_SROOK_TMPL_VT_APPLY_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/bool_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <template <class...> class F, class... Xs>
struct apply : F<Xs...> {};

template <template <class...> class F, class... Xs>
struct apply<F, packer<Xs...>> : apply<F, Xs...> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <template <class...> class F, class... Xs>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool apply_v = apply<F, Xs...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
