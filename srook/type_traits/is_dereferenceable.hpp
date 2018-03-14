// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_DEREFERENCEABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_DEREFERENCEABLE_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/is_array.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/utility/declval.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_dereferenceable_helper {
    template <class U>
    static SROOK_DECLTYPE(*declval<U&>(), SROOK_TRUE_TYPE()) test(const U&);
    static SROOK_FALSE_TYPE test(...);
};

template <class T>
struct is_nothrow_deferenceable_helper {
    template <class U>
    static bool_constant<noexcept(*declval<U&>())> test(const U&);
    static SROOK_FALSE_TYPE test(...);
};

} // namespace detail

template <class T>
struct is_dereferenceable 
    : type_traits::detail::Lor<SROOK_DECLTYPE(detail::is_dereferenceable_helper<T>::test(declval<T>())), is_pointer<T>, is_array<T>> {};

template <class T>
struct is_nothrow_dereferenceable
    : type_traits::detail::Lor<SROOK_DECLTYPE(detail::is_nothrow_deferenceable_helper<T>::test(declval<T>())), is_pointer<T>, is_array<T>> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_dereferenceable_v = is_dereferenceable<T>::value;
template <class T>
SROOK_CONSTEXPR bool is_nothrow_dereferenceable_v = is_nothrow_dereferenceable<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_dereferenceable;
using srook::type_traits::is_nothrow_dereferenceable;

} // namespace srook

#endif
