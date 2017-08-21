// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_SIN_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_SIN_HPP

#include <cmath>

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/fabs.hpp>
#include <srook/math/constants/algorithm/factorial.hpp>
#include <srook/math/constants/algorithm/fmod.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/math/constants/algorithm/pow.hpp>
#include <srook/math/constants/pi.hpp>
#include <srook/math/detail/float_compute.hpp>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE constexpr float builtin_sin(float x) SROOK_NOEXCEPT(__builtin_sinf(x))
{
    return __builtin_sinf(x);
}
SROOK_FORCE_INLINE constexpr double builtin_sin(double x) SROOK_NOEXCEPT(__builtin_sin(x))
{
    return __builtin_sin(x);
}
SROOK_FORCE_INLINE constexpr long double builtin_sin(long double x) SROOK_NOEXCEPT(__builtin_sinl(x))
{
    return __builtin_sinl(x);
}
#endif
template <typename T, class U>
inline constexpr T sin_impl2(T x, U y)
{
    return y == (10 * 2 - 1) ? std::pow(x, y) / math::factorial(y) : std::pow(x, y) / math::factorial(y) - sin_impl2(x, y + 2);
}
template <typename T>
inline constexpr T sin_impl1(T x) SROOK_NOEXCEPT(sin_impl2(math::fmod(math::PI<T>::value() - x, math::PI<T>::value())))
{
    return std::fabs(x) > math::PI<T>::value() / 2 ? sin_impl2(std::fmod(math::PI<T>::value() - x, math::PI<T>::value()) * static_cast<int>(x * 2 / math::PI<T>::value()), 1) : sin_impl2(x, 1);
}

template <typename T>
inline constexpr typename float_compute<T>::type sin_impl(T x) SROOK_NOEXCEPT(math::fmod(x, math::PI<typename detail::float_compute<T>::type>::value()))
{
    return static_cast<int>(x / math::PI<T>::value()) % 2 == 0 ? sin_impl1(std::fmod(x, math::PI<T>::value())) : -sin_impl1(std::fmod(x, math::PI<T>::value()));
}
} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr FloatType
    sin(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	SROOK_NOEXCEPT(detail::builtin_sin(x))
#else
	SROOK_NOEXCEPT(sin_impl(x))
#endif
{
    return math::isnan(x) ? x : x >= numeric_limits<FloatType>::infinity() or x <= -numeric_limits<FloatType>::infinity() ? -numeric_limits<FloatType>::quiet_NaN()
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
															  : detail::builtin_sin(x)
#else
															  : x == 0 ? x : detail::sin_impl(x)
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
    sin(IntType x) SROOK_NOEXCEPT(math::sin(static_cast<double>(x)))
{
    return math::sin(static_cast<double>(x));
}

} // namespace v1
} // namespace math

using math::sin;

} // namespace srook

#endif
