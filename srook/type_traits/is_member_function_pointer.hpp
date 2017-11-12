// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/deduced_typename.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class>
struct is_member_function_pointer_impl : SROOK_FALSE_TYPE {};

template <class T, class C>
struct is_member_function_pointer_impl<T C::*>
    : public bool_constant<is_function<T>::value> {};

} // namespace detail

template <class T>
struct is_member_function_pointer
    : public detail::is_member_function_pointer_impl<SROOK_DEDUCED_TYPENAME remove_cv<T>::type>::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits
} // namespace srook

#endif
