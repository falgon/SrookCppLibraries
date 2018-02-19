// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP
#include <srook/type_traits/is_assignable.hpp>
#include <srook/type_traits/is_referenceable.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, bool = is_referenceable<T>::value>
struct is_copy_assignable_impl;

template <class T>
struct is_copy_assignable_impl<T, false> : SROOK_FALSE_TYPE {};

template <class T>
struct is_copy_assignable_impl<T, true> : public is_assignable<T, const T&> {};

} // namespace detail

template <class T>
struct is_copy_assignable : public detail::is_copy_assignable_impl<T>::type {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_copy_assignable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_copy_assignable_v = is_copy_assignable<T>::value;
#endif

} // namespace srook

#endif
