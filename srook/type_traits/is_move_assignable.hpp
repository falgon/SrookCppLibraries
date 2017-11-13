// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP
#include <srook/type_traits/is_assignable.hpp>
#include <srook/type_traits/is_referenceable.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, bool = is_referenceable<T>::value>
struct is_move_assignable_impl;

template <class T>
struct is_move_assignable_impl<T, false> : public SROOK_FALSE_TYPE {};

template <class T>
struct is_move_assignable_impl<T, true> : public is_assignable<T&, T&&> {};

} // namespace detail

template <class T>
struct is_move_assignable : public detail::is_move_assignable_impl<T> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_move_assignable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_move_assignable_v = type_traits::is_move_assignable<T>::value;
#endif

} // namespace srook

#endif
