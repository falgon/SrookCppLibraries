// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_COPYSIGN_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_COPYSIGN_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/type_traits/float_promote.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE constexpr float builtin_copysign(float x, float y) SROOK_NOEXCEPT(__builtin_copysignf(x, y))
{
    return __builtin_copysignf(x, y);
}
SROOK_FORCE_INLINE constexpr double builtin_copysign(double x, double y) SROOK_NOEXCEPT(__builtin_copysign(x, y))
{
    return __builtin_copysign(x, y);
}
SROOK_FORCE_INLINE constexpr long double builtin_copysign(long double x, long double y) SROOK_NOEXCEPT(__builtin_copysignl(x, y))
{
    return __builtin_copysignl(x, y);
}
#endif

template <typename FloatType>
inline constexpr bool broken_signbit(FloatType x) SROOK_NOEXCEPT(math::isnan(x))
{
    return !math::isnan(x) and x < 0;
}

} // detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr FloatType
    copysign(FloatType x, FloatType y)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	SROOK_NOEXCEPT(detail::builtin_copysign(x, y))
#else
	SROOK_NOEXCEPT(noexcept(detail::broken_signbit(x)) and noexcept(detail::broken_signbit(y)) and noexcept(math::isnan(x)) and noexcept(math::isnan(y)))
#endif
{
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	detail::builtin_copysign(x, y)
#else
	x == 0 ? y == 0 ? y : detail::broken_signbit(y) ? -FloatType(0) : FloatType(0) : math::isnan(x) ? math::isnan(y) ? y : detail::broken_signbit(y) ? -numeric_limits<FloatType>::quiet_NaN() : numeric_limits<FloatType>::quiet_NaN() : detail::broken_signbit(y) != detail::broken_signbit(x) ? -x : x
#endif
	    ;
}

template <typename ArithmeticType1, typename ArithmeticType2, REQUIRES(std::is_arithmetic<ArithmeticType1>::value and std::is_arithmetic<ArithmeticType2>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr typename float_promote<ArithmeticType1, ArithmeticType2>::type
    copysign(ArithmeticType1 x, ArithmeticType2 y)
	SROOK_NOEXCEPT(math::copysign(static_cast<typename float_promote<ArithmeticType1, ArithmeticType2>::type>(x), static_cast<typename float_promote<ArithmeticType1, ArithmeticType2>::type>(y)))
{
    typedef typename float_promote<ArithmeticType1, ArithmeticType2>::type type;
    return math::copysign(static_cast<type>(x), static_cast<type>(y));
}

} // namespace v1
} // namespace math

using math::copysign;

} // namespace srook

#endif
