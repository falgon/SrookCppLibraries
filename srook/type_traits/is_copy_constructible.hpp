// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP
#include <srook/type_traits/is_constructible.hpp>
#include <srook/type_traits/is_referenceable.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, bool = is_referenceable<T>::value>
struct is_copy_constructible_impl;

template <class T>
struct is_copy_constructible_impl<T, false> : SROOK_FALSE_TYPE {
};

template <class T>
struct is_copy_constructible_impl<T, true> : public is_constructible<T, const T&> {
};

} // namespace detail

template <class T>
struct is_copy_constructible : public detail::is_copy_constructible_impl<T>::type {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_copy_constructible;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_copy_constructible_v = is_copy_constructible<T>::value;
#endif

} // namespace srook

#endif
