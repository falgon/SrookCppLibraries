// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_SCALAR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_SCALAR_HPP
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/type_traits/is_enum.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/is_member_pointer.hpp>
#include <srook/type_traits/is_nullptr.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_scalar : public integral_constant<bool, 
	is_arithmetic<T>::value || is_enum<T>::value || is_pointer<T>::value || is_member_pointer<T>::value || is_nullptr<T>::value> {};


SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_scalar;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_scalar_v = is_scalar<T>::value;
#endif

} // namespace srook

#endif
