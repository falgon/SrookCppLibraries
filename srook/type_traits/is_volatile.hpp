// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_VOLATILE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_VOLATILE_HPP

#include <srook/config.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct is_volatile : SROOK_FALSE_TYPE {};

template <class T>
struct is_volatile<volatile T> : SROOK_TRUE_TYPE {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_volatile;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_volatile_v = is_volatile<T>::value;
#endif

} // namespace srook

#endif
