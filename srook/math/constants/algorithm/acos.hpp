// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_ACOS_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_ACOS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/math/constants/pi.hpp>
#include <srook/math/constants/algorithm/asin.hpp>
#include <srook/math/constants/algorithm/fabs.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/math/detail/float_compute.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/type_traits/is_integral.hpp>

SROOK_NESTED_NAMESPACE(srook, math) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE SROOK_CONSTEXPR float builtin_acos(float x) { return __builtin_acosf(x); }
SROOK_FORCE_INLINE SROOK_CONSTEXPR double builtin_acos(double x) { return __builtin_acos(x); }
SROOK_FORCE_INLINE SROOK_CONSTEXPR long double builtin_acos(long double x) { return __builtin_acosl(x); }
#endif

template <typename T>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T acos_impl(T x) { return srook::math::PI<T>::half() - srook::math::asin(x); }
} // namespace detail

template <typename FloatType, SROOK_REQUIRES(is_floating_point<FloatType>::value)>
SROOK_CONSTEXPR
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
FloatType acos(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_NOEXCEPT(detail::builtin_acos(x))
#else
SROOK_NOEXCEPT(detail::acos_impl(x))
#endif
{
    return srook::math::isnan(x) ? x : srook::math::fabs(x) > 1 ? srook::numeric_limits<FloatType>::quiet_NaN()
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
        : srook::math::detail::builtin_acos(x)
#else
        : x == 1 ? FloatType(0)
        : static_cast<FloatType>(srook::math::detail::acos_impl(static_cast<SROOK_DEDUCED_TYPENAME srook::math::detail::float_compute<FloatType>::type>(x)))
#endif
        ;
}

template <typename IntegralType, SROOK_REQUIRES(is_integral<IntegralType>::value)>
SROOK_CONSTEXPR double acos(IntegralType x)
{
    return srook::math::acos(static_cast<double>(x));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(math, srook)

namespace srook {

using srook::math::acos;

} // namespace srook

#endif
