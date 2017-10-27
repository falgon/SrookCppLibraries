// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class>
struct is_member_pointer_impl : public SROOK_FALSE_TYPE {
};
template <class T, class C>
struct is_member_pointer_impl<T C::*> : public SROOK_TRUE_TYPE {
};

} // namespace detail

template <class T>
struct is_member_pointer : public detail::is_member_pointer_impl<typename remove_cv<T>::type>::type {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_member_pointer;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_member_pointer_v = is_member_pointer<T>::value;
#endif

} // namespace srook

#endif
