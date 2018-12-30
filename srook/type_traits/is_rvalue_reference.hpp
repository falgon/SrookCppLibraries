// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct is_rvalue_reference : SROOK_FALSE_TYPE {
};

template <class T>
struct is_rvalue_reference<T&&> : public SROOK_TRUE_TYPE {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_rvalue_reference;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
#endif

} // namespace srook

#endif
