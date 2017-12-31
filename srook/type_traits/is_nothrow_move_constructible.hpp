// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/type_traits/is_referenceable.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, bool = is_referenceable<T>::value>
struct is_nothrow_move_constructible_impl;

template <class T>
struct is_nothrow_move_constructible_impl<T, false>
    : public SROOK_FALSE_TYPE {
};

template <class T>
struct is_nothrow_move_constructible_impl<T, true>
    : public is_nothrow_constructible<T, T&&> {
};

} // namespace detail

template <class T>
struct is_nothrow_move_constructible : public detail::is_nothrow_move_constructible_impl<T> {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_nothrow_move_constructible;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_move_constructible_v = type_traits::is_nothrow_move_constructible<T>::value;
#endif

} // namespace srook

#endif
