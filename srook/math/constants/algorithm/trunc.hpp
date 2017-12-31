// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_TRUNC_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_TRUNC_HPP

#include <cstdint>
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <stdexcept>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE constexpr float builtin_trunc(float x) SROOK_NOEXCEPT(__builtin_truncf(x))
{
    return __builtin_truncf(x);
}

SROOK_FORCE_INLINE constexpr double builtin_trunc(double x) SROOK_NOEXCEPT(__builtin_trunc(x))
{
    return __builtin_trunc(x);
}

SROOK_FORCE_INLINE constexpr long double builtin_trunc(long double x) SROOK_NOEXCEPT(__builtin_truncl(x))
{
    return __builtin_truncl(x);
}
#endif
} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
constexpr FloatType trunc(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
    SROOK_NOEXCEPT(detail::builtin_trunc(x))
#else
    SROOK_NOEXCEPT(numeric_limits<std::uintmax_t>::max() < x or numeric_limits<std::uintmax_t>::max < -x ? numeric_limits<FloatType>::quiet_NaN() : x < 0 ? -static_cast<FloatType>(static_cast<std::uintmax_t>(-x)) : static_cast<FloatType>(static_cast<std::uintmax_t>(x)))
#endif
{
    return isnan(x) ? x : x >= numeric_limits<FloatType>::infinity() ? numeric_limits<FloatType>::infinity() : x <= -numeric_limits<FloatType>::infinity() ? -numeric_limits<FloatType>::infinity()
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
																			   : detail::builtin_trunc(x)
#else
																			   : x == 0 ? x : numeric_limits<std::uintmax_t>::max() < x or numeric_limits<std::uintmax_t>::max() < -x ? numeric_limits<FloatType>::quiet_NaN() : x < 0 ? -static_cast<FloatType>(static_cast<std::uintmax_t>(-x)) : static_cast<FloatType>(static_cast<std::uintmax_t>(x))
#endif
	;
}

template <typename IntType, REQUIRES(std::is_integral<IntType>::value)>
SROOK_FORCE_INLINE constexpr double trunc(IntType x) SROOK_NOEXCEPT(trunc(static_cast<double>(x)))
{
    return trunc(static_cast<double>(x));
}

} // namespace v1
} // namespace math

using math::trunc;

} // namespace srook

#endif
