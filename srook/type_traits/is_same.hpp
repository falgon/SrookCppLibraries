// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_SAME_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_SAME_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
template <class, class>
struct is_same : SROOK_FALSE_TYPE {};

template <class T>
struct is_same<T, T> : SROOK_TRUE_TYPE {};
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_same;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
constexpr bool is_same_v = is_same<L, R>::value;
#endif

} // namespace srook
#endif
