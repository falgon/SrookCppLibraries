// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_NULLPTR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_NULLPTR_HPP
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/config/libraries/nullptr.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

#define DEFINE_IS_TRUE_NULLPTR(TYPE)\
	template <>\
	struct is_nullptr_impl<TYPE> : public SROOK_TRUE_TYPE {}

template <class>
struct is_nullptr_impl : public SROOK_FALSE_TYPE {};

DEFINE_IS_TRUE_NULLPTR(SROOK_NULLPTR_T);

#undef DEFINE_IS_TRUE_NULLPTR

} // namespace detail

template <class T>
struct is_nullptr : detail::is_nullptr_impl<typename remove_cv<T>::type>::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_nullptr;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class U>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nullptr_v = is_nullptr<T>::value;
#endif

} // namespace srook

#endif
