// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_SWAP_ABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_SWAP_ABLE_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/config.hpp>
#include <srook/type_traits/is_tuple.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_move_constructible.hpp>
#include <srook/type_traits/is_move_assignable.hpp>
#include <srook/type_traits/is_nothrow_move_constructible.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/utility/declval.hpp>
#include <type_traits>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_swappable;

template <class T>
struct is_nothrow_swappable;

namespace detail {

template <class T>
inline SROOK_DEDUCED_TYPENAME 
enable_if<Land<Lnot<is_tuple<T>>, is_move_constructible<T>, is_move_assignable<T>>::value>::type
swap(T&, T&)
noexcept(Land<is_nothrow_move_constructible<T>, std::is_nothrow_move_assignable<T>>::value);

template <class T, std::size_t n>
inline SROOK_DEDUCED_TYPENAME
enable_if<is_swappable<T>::value>::type
swap(T (&)[n], T (&)[n])
noexcept(is_nothrow_swappable<T>::value);

namespace swappable_ns {

using std::swap;

struct do_is_swappable {
    template <class T, class = SROOK_DECLTYPE(swap(declval<T&>(), declval<T&>()))>
    static SROOK_TRUE_TYPE test(int);
    template <class>
    static SROOK_FALSE_TYPE test(...);
};

struct do_is_nothrow_swappable {
    template <class T>
    static bool_constant<noexcept(swap(declval<T&>(), declval<T&>()))> test(int);
    template <class>
    static SROOK_FALSE_TYPE test(...);
};

struct do_is_swappable_with {
    template <class T, class U, class = SROOK_DECLTYPE(swap(declval<T>(), declval<U>())), class = SROOK_DECLTYPE(swap(declval<U>(), declval<T>()))>
    static SROOK_TRUE_TYPE test(int);

    template <class, class>
    static SROOK_FALSE_TYPE test(...);
};

struct do_is_nothrow_swappable_with {
    template <class T, class U>
    static bool_constant<noexcept(swap(declval<T>(), declval<U>())) && noexcept(swap(declval<U>(), declval<T>()))>
    test(int);

    template <class, class>
    static SROOK_FALSE_TYPE test(...);
};

} // namespace swappable_ns

template <class T>
struct is_swappable_impl : public swappable_ns::do_is_swappable {
    typedef SROOK_DECLTYPE(test<T>(0)) type;
};

template <class T>
struct is_nothrow_swappable_impl : public swappable_ns::do_is_nothrow_swappable {
    typedef SROOK_DECLTYPE(test<T>(0)) type;
};

template <class T, class U>
struct is_swappable_with_impl : public swappable_ns::do_is_swappable_with {
    typedef SROOK_DECLTYPE(test<T, U>(0)) type;
};

template <class T>
struct is_swappable_with_impl<T&, T&> : public swappable_ns::do_is_swappable {
    typedef SROOK_DECLTYPE(test<T&>(0)) type;
};

template <class T, class U>
struct is_nothrow_swappable_with_impl : public swappable_ns::do_is_nothrow_swappable_with {
    typedef SROOK_DECLTYPE(test<T, U>(0)) type;
};

template <class T>
struct is_nothrow_swappable_with_impl<T&, T&> : public swappable_ns::do_is_swappable {
    typedef SROOK_DECLTYPE(test<T&>(0)) type;
};

} // namespace detail

template <class T>
struct is_swappable : public detail::is_swappable_impl<T>::type {};

template <class T>
struct is_nothrow_swappable : public detail::is_nothrow_swappable_impl<T>::type {};

template <class T, class U>
struct is_swappable_with : public detail::is_swappable_with_impl<T, U>::type {};

template <class T, class U>
struct is_nothrow_swappable_with : public detail::is_nothrow_swappable_with_impl<T, U>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_swappable_v = is_swappable<T>::value;

template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;

template <class T, class U>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_swappable_with_v = is_swappable_with<T, U>::value;

template <class T, class U>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_swappable;
using srook::type_traits::is_nothrow_swappable;
using srook::type_traits::is_swappable_with;
using srook::type_traits::is_nothrow_swappable_with;

} // namespace srook

#endif
#endif
