// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_COS_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_COS_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/constants/algorithm/factorial.hpp>
#include <srook/math/constants/algorithm/fmod.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/math/constants/algorithm/sin.hpp>
#include <srook/math/constants/pi.hpp>
#include <srook/math/detail/float_compute.hpp>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE constexpr float builtin_cos(float x) SROOK_NOEXCEPT(__builtin_cosf(x))
{
    return __builtin_cosf(x);
}
SROOK_FORCE_INLINE constexpr double builtin_cos(double x) SROOK_NOEXCEPT(__builtin_cos(x))
{
    return __builtin_cos(x);
}
SROOK_FORCE_INLINE constexpr long double builtin_cos(long double x) SROOK_NOEXCEPT(__builtin_cosl(x))
{
    return __builtin_cosl(x);
}
#endif

} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr FloatType
    cos(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	SROOK_NOEXCEPT(detail::builtin_cos(x))
#else
	SROOK_NOEXCEPT(noexcept(math::fmod(x, FloatType())) and noexcept(math::sin(FloatType())))
#endif
{
    return math::isnan(x) ? x : x >= numeric_limits<FloatType>::infinity() or x <= -numeric_limits<FloatType>::infinity() ? -numeric_limits<FloatType>::quiet_NaN()
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
															  : detail::builtin_cos(x)
#else
															  : x == 0 ? FloatType(1) : math::fmod(x, math::PI<typename detail::float_compute<FloatType>::type>::value() * 2) == math::PI<typename detail::float_compute<FloatType>::type>::value() / 2 ? 0 : math::sin(x + math::PI<typename detail::float_compute<FloatType>::type>::value() / 2);
#endif
	;
}

template <typename IntType, REQUIRES(std::is_integral<IntType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr double
    cos(IntType x) SROOK_NOEXCEPT(math::cos(static_cast<double>(x)))
{
    return math::cos(static_cast<double>(x));
}

} // namespace v1
} // namespace math

using math::cos;

} // namespace srook

#endif
