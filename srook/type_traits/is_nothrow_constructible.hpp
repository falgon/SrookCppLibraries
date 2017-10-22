// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
#include <srook/type_traits/is_constructible.hpp>
#include <srook/type_traits/is_nothrow_default_constructible.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, class... Args>
struct is_nothrow_constructible_impl : 
public conditional<noexcept(T(declval<Args>()...)), SROOK_TRUE_TYPE, SROOK_FALSE_TYPE>::type {};

template <class T, class Arg>
struct is_nothrow_constructible_impl<T, Arg> :
public conditional<noexcept(static_cast<T>(declval<Arg>())), SROOK_TRUE_TYPE, SROOK_FALSE_TYPE>::type {};

template <class T>
struct is_nothrow_constructible_impl<T> : public is_nothrow_default_constructible<T> {};

} // namespace detail

template <class T, class... Args>
struct is_nothrow_constructible : 
public detail::Land<is_constructible<T, Args...>, detail::is_nothrow_constructible_impl<T, Args...>> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_nothrow_constructible;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_constructible_v = type_traits::is_nothrow_constructible<T>::value;
#endif

} // namespace srook

#endif
