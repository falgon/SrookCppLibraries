// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
#include <srook/config.hpp>
#include <srook/type_traits/is_referenceable.hpp>
#include <srook/type_traits/type_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T, bool = is_referenceable<T>::value>
struct add_lvalue_reference_impl : public type_constant<T> {};

template <class T>
struct add_lvalue_reference_impl<T, true> : public type_constant<T&> {};

} // namespace detail
SROOK_INLINE_NAMESPACE_END

template <class T>
struct add_lvalue_reference : public srook::type_traits::detail::add_lvalue_reference_impl<T> {};

} // namespace type_traits

using type_traits::add_lvalue_reference;

#if SROOK_CPP_ALIAS_TEMPLATES

template <class T>
using add_lvalue_reference_t = SROOK_DEDUCED_TYPENAME srook::type_traits::add_lvalue_reference<T>::type;

#endif

} // namespace srook
#endif
