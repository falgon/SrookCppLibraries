// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_REFERENCE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_REFERENCE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_lvalue_reference.hpp>
#include <srook/type_traits/is_rvalue_reference.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_reference : public integral_constant<bool, (is_lvalue_reference<T>::value || is_rvalue_reference<T>::value)> {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_reference;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_reference_v = is_reference<T>::value;
#endif

} // namespace srook

#endif
