// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_OBJECT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_OBJECT_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/is_reference.hpp>
#include <srook/type_traits/is_void.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_object : public integral_constant<bool, !(is_function<T>::value || is_reference<T>::value || is_void<T>::value)> {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_object;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_object_v = is_object<T>::value;
#endif

} // namespace srook

#endif
