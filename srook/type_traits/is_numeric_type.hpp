// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_TYPETRAITS_IS_NUMERIC_TYPE_HPP
#define INCLUDED_SROOK_MPL_TYPETRAITS_IS_NUMERIC_TYPE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/is_abstract.hpp>
#include <srook/type_traits/is_default_constructible.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
#include <srook/type_traits/is_destructible.hpp>
#include <srook/type_traits/is_assignable.hpp>
#include <srook/type_traits/is_reference.hpp>
#include <srook/type_traits/is_referenceable.hpp>
#include <srook/type_traits/is_const.hpp>
#include <srook/type_traits/is_volatile.hpp>
#include <srook/type_traits/is_class.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_numeric_type_impl
    : type_traits::detail::Land<
        type_traits::detail::Lnot<is_reference<T>>,
        type_traits::detail::Lnot<is_const<T>>,
        type_traits::detail::Lnot<is_volatile<T>>,
        SROOK_DEDUCED_TYPENAME conditional<
            is_class<T>::value, 
            type_traits::detail::Land<
                is_default_constructible<T>,
                is_copy_constructible<T>,
                is_destructible<T>,
                is_assignable<T, T&>,
                is_referenceable<T>,
                type_traits::detail::Lnot<is_abstract<T>>
            >,
            SROOK_TRUE_TYPE
        >::type
      > {};

} // namespace detail

template <class T>
struct is_numeric_type : detail::is_numeric_type_impl<T> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_numeric_type_v = is_numeric_type<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_numeric_type;

} // namespace srook
#endif
