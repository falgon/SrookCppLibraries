// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_RANK_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_RANK_HPP

#include <srook/config/feature.hpp>
#include <srook/type_traits/integral_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct rank : public integral_constant<std::size_t, 0> {};

template <class T, std::size_t Size>
struct rank<T[Size]> : public integral_constant<std::size_t, 1 + rank<T>::value> {};

template <class T>
struct rank<T[]> : public integral_constant<std::size_t, 1 + rank<T>::value> {};

SROOK_INLINE_NAMESPACE_END
} // type_traits

using type_traits::rank;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool rank_v = rank<T>::value;
#endif

} // namespace srook

#endif
