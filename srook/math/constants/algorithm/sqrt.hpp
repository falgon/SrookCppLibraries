// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_SQRT_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_SQRT_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/math/detail/float_compute.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR

SROOK_FORCE_INLINE constexpr float builtin_sqrt(float x) SROOK_NOEXCEPT(__builtin_sqrtf(x))
{
    return __builtin_sqrtf(x);
}

SROOK_FORCE_INLINE constexpr double builtin_sqrt(double x) SROOK_NOEXCEPT(__builtin_sqrt(x))
{
    return __builtin_sqrt(x);
}

SROOK_FORCE_INLINE constexpr long double builtin_sqrt(long double x) SROOK_NOEXCEPT(__builtin_sqrtl(x))
{
    return __builtin_sqrtl(x);
}

#endif

template <typename T>
inline T sqrt_impl2(T x, T s, T s2)
{
    return !(s < s2) ? s2 : sqrt_impl2(x, (x / s + s) / 2, s);
}
template <typename T>
inline T sqrt_impl1(T x, T s)
{
    return sqrt_impl2(x, (x / s + s) / 2, s);
}
template <typename T>
inline T sqrt_impl(T x)
{
    return sqrt_impl1(x, x > 1 ? x : T(1));
}
}

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
constexpr FloatType sqrt(FloatType x)
{
    return isnan(x) ? x
		    : x >= numeric_limits<FloatType>::infinity() ? numeric_limits<FloatType>::infinity()
								 : x < 0 ? -numeric_limits<FloatType>::quiet_NaN()
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
									 : detail::builtin_sqrt(x)
#else
									 : x == 0 ? x
										  : static_cast<FloatType>(detail::sqrt_impl(static_cast<typename detail::float_compute<FloatType>::type>(x)))
#endif
	;
}

template <typename IntType, REQUIRES(std::is_integral<IntType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline 
#endif
constexpr double sqrt(IntType x)
{
    return sqrt(static_cast<double>(x));
}

} // namespace v1
} // namespace math

using math::sqrt;

} // namespace srook

#endif
