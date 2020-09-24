// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_assignable.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class U>
struct is_nothrow_assignable : integral_constant<bool, is_assignable<T, U>::value && noexcept(declval<T>() = declval<U>())> {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_nothrow_assignable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class U>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_assignable_v = is_nothrow_assignable<T, U>::value;
#endif

} // namespace srook

#endif
