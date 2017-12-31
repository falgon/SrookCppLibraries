// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CONST_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CONST_HPP

#include <srook/config.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct is_const : SROOK_FALSE_TYPE {};

template <class T>
struct is_const<const T> : SROOK_TRUE_TYPE {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_const;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_const_v = is_const<T>::value;
#endif

} // namespace srook

#endif
