// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_TYPETRAITS_CLOCK_IS_CLOCK_HPP
#define INCLUDED_SROOK_MPL_TYPETRAITS_CLOCK_IS_CLOCK_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/detail/sfinae_types.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/is_same.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_clock_impl : sfinae_types {
private:
    template <class U, bool = U::is_steady>
    static SROOK_DEDUCED_TYPENAME conditional<is_same<SROOK_DECLTYPE(U::now()), SROOK_DEDUCED_TYPENAME U::time_point>::value, one, two>::type
    test(SROOK_DEDUCED_TYPENAME U::rep*, SROOK_DEDUCED_TYPENAME U::period*, SROOK_DEDUCED_TYPENAME U::time_point*);
    template <class>
    static two test(...);
public:
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool value = sizeof(test<T>(0, 0, 0)) == sizeof(one);
};

} // namespace detail

template <class C>
struct is_clock : detail::is_clock_impl<C> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_clock_v = is_clock<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_clock;

} // namespace srook
#endif
