// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_LOG_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_LOG_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/factorial.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/math/constants/algorithm/sqrt.hpp>
#include <srook/math/constants/root.hpp>
#include <srook/math/detail/float_compute.hpp>
#include <srook/math/detail/pow.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE constexpr float builtin_log(float x) SROOK_NOEXCEPT(__builtin_logf(x))
{
    return __builtin_logf(x);
}
SROOK_FORCE_INLINE constexpr double builtin_log(double x) SROOK_NOEXCEPT(__builtin_log(x))
{
    return __builtin_log(x);
}
SROOK_FORCE_INLINE constexpr long double builtin_log(long double x) SROOK_NOEXCEPT(__builtin_logl(x))
{
    return __builtin_logl(x);
}
#endif

template <typename T>
inline constexpr T log_impl2(T x, std::size_t n, std::size_t last) SROOK_NOEXCEPT(detail::pow_n(x, n))
{
    return last - n == 1 ? (n % 2 ? 1 : -1) * detail::pow_n(x, n) / n : detail::log_impl2(x, n, n + (last - n) / 2) + detail::log_impl2(x, n + (last - n) / 2, last);
}
template <typename T>
inline constexpr T log_impl1(T x) SROOK_NOEXCEPT(detail::log_impl2(x - T(1), 1, math::factorial_limit<T>() + 1))
{
    return !(x > root_two<T>()) ? detail::log_impl2(x - T(1), 1, std::size_t(math::factorial_limit<T>())) + 1 : T(2) * detail::log_impl1(math::sqrt(x));
}
template <typename T>
inline constexpr T log_impl(T x) SROOK_NOEXCEPT(detail::log_impl1(T(1) / x))
{
    return x < -1 ? -detail::log_impl1(T(1) / x) : detail::log_impl1(x);
}

} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
constexpr FloatType log(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
    SROOK_NOEXCEPT(detail::builtin_log(x))
#else
    SROOK_NOEXCEPT(detail::log_impl(static_cast<typename detail::float_compute<FloatType>::type>(x)))
#endif
{
    return math::isnan(x) ? x : x == 0 ? -numeric_limits<FloatType>::infinity() : x >= numeric_limits<FloatType>::infinity() ? numeric_limits<FloatType>::infinity() : x < 0 ? numeric_limits<FloatType>::quiet_NaN()
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
																					     : detail::builtin_log(x)
#else
																					     : static_cast<FloatType>(detail::log_impl(static_cast<typename detail::float_compute<FloatType>::type>(x)))
#endif
	;
}

template <typename IntType, REQUIRES(std::is_integral<IntType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
constexpr double log(IntType x) SROOK_NOEXCEPT(math::log(static_cast<double>(x)))
{
    return math::log(static_cast<double>(x));
}

} // namespace v1
} // namespace math

using math::log;

} // namespace srook

#endif
