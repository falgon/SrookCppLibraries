// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_TYPETRAITS_CLOCK_IS_TRIVIAL_CLOCK_HPP
#define INCLUDED_SROOK_MPL_TYPETRAITS_CLOCK_IS_TRIVIAL_CLOCK_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/type_traits/clock/is_clock.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/type_traits/is_less_than_comparable.hpp>
#include <srook/type_traits/is_default_constructible.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
#include <srook/type_traits/is_copy_assignable.hpp>
#include <srook/type_traits/is_destructible.hpp>
#include <srook/type_traits/is_numeric_type.hpp>
#include <srook/type_traits/is_swappable.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {
template <class... Ts>
struct trivially_requires 
    : type_traits::detail::Land<
        type_traits::detail::Land<is_equality_comparable<Ts>...>,
        type_traits::detail::Land<is_less_than_comparable<Ts>...>,
        type_traits::detail::Land<is_default_constructible<Ts>...>,
        type_traits::detail::Land<is_copy_constructible<Ts>...>,
        type_traits::detail::Land<is_copy_assignable<Ts&>...>,
        type_traits::detail::Land<is_destructible<Ts>...>,
        type_traits::detail::Land<is_numeric_type<Ts>...>,
        type_traits::detail::Land<srook::is_swappable<Ts&>...>
      > {};

template <class T>
struct is_trivial_clock_impl2 
    : type_traits::detail::Land<
        trivially_requires<SROOK_DEDUCED_TYPENAME T::rep, SROOK_DEDUCED_TYPENAME T::duration, SROOK_DEDUCED_TYPENAME T::time_point>,
        bool_constant<noexcept(T::now())>
      > {};

template <class T>
struct is_trivial_clock_impl
    : conditional<
        is_clock<T>::value,
        is_trivial_clock_impl2<T>,
        SROOK_FALSE_TYPE
      >::type {};

} // namespace detail

template <class C>
struct is_trivial_clock : detail::is_trivial_clock_impl<C> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_trivial_clock_v = is_trivial_clock<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_trivial_clock;

} // namespace srook
#endif
