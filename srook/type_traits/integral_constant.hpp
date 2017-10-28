// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/explicit.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <type_traits>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T, T v>
struct integral_constant {
    static SROOK_CONSTEXPR_OR_CONST T value = v;
    typedef T value_type;
    typedef integral_constant type;

    SROOK_CONSTEXPR_OR_CONST operator value_type() const SROOK_NOEXCEPT_TRUE { return value; }
    SROOK_CONSTEXPR_OR_CONST value_type operator()() const SROOK_NOEXCEPT_TRUE { return value; }
#if SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS
    SROOK_EXPLICIT SROOK_CONSTEXPR_OR_CONST operator std::integral_constant<T, v>() const SROOK_NOEXCEPT_TRUE { return std::integral_constant<T, v>(); }
#endif
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::integral_constant;

} // namespace srook

#endif
