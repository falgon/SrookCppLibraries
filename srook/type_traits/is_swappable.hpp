// Copyright (C) 2017 roki

#ifndef INCLUDED_SROOK_TYPE_TRAITS_SWAP_ABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_SWAP_ABLE_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <type_traits>
#include <utility>

namespace srook {
namespace type_traits {
namespace detail {

template <class T> struct is_swappable;
template <class T> struct is_nothrow_swappable;
template <class T> struct is_swappable_with;
template <class T> struct is_nothrow_swappable_with;

template <class T>
SROOK_INLINE_VARIABLE typename std::enable_if<std::is_move_constructible<T>::value && std::is_move_assignable<T>::value>::type
swap(T &, T &) noexcept(std::is_nothrow_move_constructible<T>() && std::is_nothrow_move_assignable<T>());

template <class T, std::size_t n>
SROOK_INLINE_VARIABLE typename std::enable_if<is_swappable<T>::value>::type
swap(T (&a)[n], T (&b)[n]) noexcept(is_nothrow_swappable<T>::value);

struct detect_is_swappable {
	template <class T, class = decltype(swap(std::declval<T&>(), std::declval<T&>()))>
	static std::true_type tester(int);

	template <class>
	static std::false_type tester(...);
};

struct detect_is_nothrow_swappable {
    template <class T>
    static auto tester(int) -> std::integral_constant<bool, noexcept(swap(std::declval<T &>(), std::declval<T &>()))>;

    template <class>
    static std::false_type tester(...);
};

struct detect_is_swappable_with {
    template <class T, class U, class = decltype(swap(std::declval<T>(), std::declval<U>())), class = decltype(swap(std::declval<U>(), std::declval<T>()))>
    static std::true_type tester(int);

    template <class, class>
    static std::false_type tester(...);
};

struct detect_is_nothrow_swappable_with {
    template <class T, class U>
    static auto tester(int) -> std::integral_constant<bool, noexcept(swap(std::declval<T>(), std::declval<U>())) && noexcept(swap(std::declval<U>(), std::declval<T>()))>;

    template <class, class>
    static std::false_type tester(...);
};

template <class T>
struct is_swappable_impl : decltype(detect_is_swappable::tester<T>(0)) {};

template <class T>
struct is_nothrow_swappable_impl : decltype(detect_is_nothrow_swappable::tester<T>(0)) {};

template <class T, class U>
struct is_swappable_with_impl : decltype(detect_is_swappable_with::tester<T, U>(0)) {};

template <class T>
struct is_swappable_with_impl<T &, T &> : decltype(detect_is_swappable::tester<T &>(0)) {};

template <class T, class U>
struct is_nothrow_swappable_with_impl : decltype(detect_is_nothrow_swappable_with::tester<T, U>(0)) {};

template <class T>
struct is_nothrow_swappable_with_impl<T &, T &> : decltype(detect_is_nothrow_swappable::tester<T &>(0)) {};

} // namespace detail

template <class T>
struct is_swappable : detail::is_swappable_impl<T> {};

template <class T>
struct is_nothrow_swappable : detail::is_nothrow_swappable_impl<T> {};

template <class T, class U>
struct is_swappable_with : detail::is_swappable_with_impl<T, U> {};

template <class T, class U>
struct is_nothrow_swappable_with : detail::is_nothrow_swappable_with_impl<T, U> {};


} // namespace type_traits

using type_traits::is_swappable;
using type_traits::is_nothrow_swappable;
using type_traits::is_swappable_with;
using type_traits::is_nothrow_swappable_with;

#if SROOK_CPP_VARIABLE_TEMPLATES

template <class T>
SROOK_INLINE_VARIABLE constexpr bool is_swappable_v = is_swappable<T>();

template <class T>
SROOK_INLINE_VARIABLE constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>();

template <class T, class U>
SROOK_INLINE_VARIABLE constexpr bool is_swappable_with_v = is_swappable_with<T, U>();

template <class T, class U>
SROOK_INLINE_VARIABLE constexpr bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>();

#endif

} // namespace srook

#endif
