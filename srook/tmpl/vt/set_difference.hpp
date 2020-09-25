// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_SET_DIFFERENCE_HPP
#define INCLUDED_SROOK_TMPL_VT_SET_DIFFERENCE_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/unique.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/not_fn.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/tmpl/vt/is_contained_in.hpp>
#include <srook/type_traits/conditional.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, class... U>
struct contained_if
    : conditional<not_fn<is_contained_in>::type<T, U...>::value, T, packer<>> {};

template <class T, class... U>
struct contained_if<T, packer<U...>> : contained_if<T, U...> {};

template <class, class>
struct set_difference_impl1;

template <class X, class... Xs, class R>
struct set_difference_impl1<packer<X, Xs...>, R>
    : concat<
        SROOK_DEDUCED_TYPENAME contained_if<X, R>::type,
        SROOK_DEDUCED_TYPENAME set_difference_impl1<packer<Xs...>, R>::type
    > {};
    
template <class... R>
struct set_difference_impl1<packer<>, packer<R...>> 
    : type_constant<packer<>> {};

template <class L, class R>
struct set_difference_impl2 
    : set_difference_impl1<
        SROOK_DEDUCED_TYPENAME unique<L>::type,
        SROOK_DEDUCED_TYPENAME unique<R>::type
      > {};

} // namespace detail

template <class L, class R>
struct set_difference : detail::set_difference_impl2<L, R> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R>
using set_difference_t = SROOK_DEDUCED_TYPENAME set_difference<L, R>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
