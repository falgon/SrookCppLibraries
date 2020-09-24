// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ERASE_IF_HPP
#define INCLUDED_SROOK_TMPL_VT_ERASE_IF_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/type_traits/type_constant.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1) 

namespace detail {

template <bool, class>
struct erase_if_impl : type_constant<packer<>> {};

template <class T>
struct erase_if_impl<false, T> : type_constant<T> {};

} // namespace detail

template <template <class...> class, class...>
struct erase_if;

template <template <class...> class F, class X, class... Xs>
struct erase_if<F, X, Xs...>
    : concat<
        SROOK_DEDUCED_TYPENAME detail::erase_if_impl<F<X>::value, X>::type,
        SROOK_DEDUCED_TYPENAME erase_if<F, Xs...>::type
      > {};

template <template <class...> class F>
struct erase_if<F> : type_constant<packer<>> {};

template <template <class...> class F, class... Xs>
struct erase_if<F, packer<Xs...>> : erase_if<F, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class F, class... Xs>
using erase_if_t = SROOK_DEDUCED_TYPENAME erase_if<F, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
