// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_POINTER_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_POINTER_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class>
struct is_pointer_impl : public SROOK_FALSE_TYPE {};
template <class T>
struct is_pointer_impl<T*> : public SROOK_TRUE_TYPE {};

} // namespace detail

template <class T>
struct is_pointer : public detail::is_pointer_impl<typename remove_cv<T>::type>::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_pointer;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_pointer_v = is_pointer<T>::value;
#endif

} // namespace srook

#endif
