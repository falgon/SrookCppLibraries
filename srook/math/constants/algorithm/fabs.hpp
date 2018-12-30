// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_FABS_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_FABS_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/copysign.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE constexpr float builtin_fabs(float x) SROOK_NOEXCEPT(__builtin_fabsf(x))
{
    return __builtin_fabsf(x);
}
SROOK_FORCE_INLINE constexpr double builtin_fabs(double x) SROOK_NOEXCEPT(__builtin_fabs(x))
{
    return __builtin_fabs(x);
}
SROOK_FORCE_INLINE constexpr long double builtin_fabs(long double x) SROOK_NOEXCEPT(__builtin_fabsl(x))
{
    return __builtin_fabsl(x);
}
#endif

} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
constexpr FloatType fabs(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
    SROOK_NOEXCEPT(detail::builtin_fabs(x))
#else
    SROOK_NOEXCEPT(noexcept(math::isnan(x)) and noexcept(numeric_limits<FloatType>::quiet_NaN()) and noexcept(math::copysign(x, FloatType(0))))
#endif
{
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	detail::builtin_fabs(x)
#else
	math::isnan(x) ? numeric_limits<FloatType>::quiet_NaN() : x < 0 ? -x : x 
#endif
	    ;
}

template <typename IntType, REQUIRES(std::is_integral<IntType>::value)>
SROOK_FORCE_INLINE constexpr double fabs(IntType x) SROOK_NOEXCEPT(math::fabs(static_cast<double>(x)))
{
    return math::fabs(static_cast<double>(x));
}

} // namespace v1
} // namespace math

using math::fabs;

} // namespace srook

#endif
