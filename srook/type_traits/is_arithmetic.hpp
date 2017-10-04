// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_ARITHMETIC_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_ARITHMETIC_HPP
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/is_floating_point.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_arithmetic : public integral_constant<bool, is_integral<T>::value || is_floating_point<T>::value> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_arithmetic;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class U>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_arithmetic_v = is_arithmetic<T>::value;
#endif

} // namespace srook

#endif
