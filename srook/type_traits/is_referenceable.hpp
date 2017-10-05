// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_REFERENCEABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_REFERENCEABLE_HPP
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_reference.hpp>
#include <srook/type_traits/is_object.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_referenceable : public integral_constant<bool, is_object<T>::value || is_reference<T>::value> {};

template <class R, class... Args>
struct is_referenceable<R(Args...)> : public SROOK_TRUE_TYPE {};

template <class R, class... Args>
struct is_referenceable<R(Args......)> : public SROOK_TRUE_TYPE {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_referenceable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_referenceable_v = is_referenceable<T>::value;
#endif

} // namespace srook

#endif
