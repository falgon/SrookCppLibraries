// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_VOID_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_VOID_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/remove_cv.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class>
struct is_void_impl : public SROOK_FALSE_TYPE {};

template <>
struct is_void_impl<void> : public SROOK_TRUE_TYPE {};

} // namespace detail

template <class T>
struct is_void : public integral_constant<bool, (detail::is_void_impl<typename remove_cv<T>::type>::value)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_void;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_void_v = is_void<T>::value;
#endif

} // namespace srook

#endif
