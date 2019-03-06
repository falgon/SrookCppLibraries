// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP

#include <srook/type_traits/is_trivially_constructible.hpp>
#include <srook/type_traits/is_copy_assignable.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_referenceable.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, bool = is_referenceable<T>::value>
struct is_trivially_copy_assignable_impl;

template <class T>
struct is_trivially_copy_assignable_impl<T, false> : public SROOK_FALSE_TYPE {};

template <class T>
struct is_trivially_copy_assignable_impl<T, true> 
    : public Land<is_copy_assignable<T>, bool_constant<__is_trivially_constructible(T, const T&)>> {};

} // namespace detail

template <class T>
struct is_trivially_copy_assignable : public detail::is_trivially_copy_assignable_impl<T> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_trivially_copy_assignable;

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <class T, class>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_trivially_copy_assignable_v = is_trivially_copy_assignable<T>::value;
#    endif

} // namespace srook

#endif
