// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_EXTENT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_EXTENT_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <cstddef>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class, unsigned = 0>
struct extent : public integral_constant<std::size_t, 0> {};

template <class T, unsigned UInt, std::size_t size>
struct extent<T[size], UInt> : public integral_constant<std::size_t, UInt == 0 ? size : extent<T, UInt - 1>::value> {};

template <class T, unsigned UInt>
struct extent<T[], UInt> : public integral_constant<std::size_t, UInt == 0 ? 0 : extent<T, UInt - 1>::value> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::extent;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, unsigned I>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR std::size_t extent_v = extent<T, I>::value;
#endif

} // namespace srook

#endif
