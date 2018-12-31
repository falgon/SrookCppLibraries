// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#include <srook/config/feature.hpp>
#include <srook/config/attribute/visibility.hpp>
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <utility>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T, T v>
struct integral_constant {
    static SROOK_CONSTEXPR_OR_CONST T value = v;
    typedef T value_type;
    typedef integral_constant type;

    SROOK_CONSTEXPR_OR_CONST SROOK_FORCE_INLINE
    operator value_type() const SROOK_NOEXCEPT_TRUE { return value; }
    SROOK_CONSTEXPR_OR_CONST SROOK_FORCE_INLINE
    value_type operator()() const SROOK_NOEXCEPT_TRUE { return value; }
#if SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS
    SROOK_CONSTEXPR_OR_CONST SROOK_ATTRIBUTE_INLINE_VISIBILITY
    operator std::integral_constant<T, v>() const SROOK_NOEXCEPT_TRUE { return std::integral_constant<T, v>(); }
#endif
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::integral_constant;

} // namespace srook

#endif
