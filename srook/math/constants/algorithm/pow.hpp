#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_POWER_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_POWER_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/copysign.hpp>
#include <srook/math/constants/algorithm/fabs.hpp>
#include <srook/math/constants/algorithm/is_integer.hpp>
#include <srook/math/constants/algorithm/is_odd.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/math/detail/float_compute.hpp>

namespace srook {
namespace math {
inline namespace v1 {

namespace detail {
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE constexpr float builtin_pow(float x, float y) SROOK_NOEXCEPT(__builtin_powf(x, y))
{
    return __builtin_powf(x, y);
}
SROOK_FORCE_INLINE constexpr double builtin_pow(double x, double y) SROOK_NOEXCEPT(__builtin_pow(x, y))
{
    return __builtin_pow(x, y);
}
SROOK_FORCE_INLINE constexpr long double builtin_pow(long double x, long double y) SROOK_NOEXCEPT(__builtin_powl(x, y))
{
    return __builtin_powl(x, y);
}
#endif
template <typename T>
inline constexpr T pow_impl(T x, T y) SROOK_NOEXCEPT_TRUE
{
    return y <= 0 ? 1 : pow_impl(x, y - 1) * x;
}

} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr FloatType
    pow(FloatType x, FloatType y)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	SROOK_NOEXCEPT(detail::builtin_pow(x, y))
#else
	SROOK_NOEXCEPT(noexcept(is_odd(x)) and noexcept(is_odd(y)) and noexcept(math::fabs(x)) and noexcept(math::fabs(y)) and noexcept(math::isnan(x)))
#endif
{
    return x == 1 ? FloatType(1)
		  : y == 0 ? FloatType(1)
			   : math::isnan(y) ? y
					    : math::isnan(x) ? x
							     : x == 0 ? y < 0 ? math::is_odd(y) ? math::copysign(numeric_limits<FloatType>::infinity(), x)
												: numeric_limits<FloatType>::infinity()
									      : math::is_odd(y) ? x
												: FloatType(0)
								      : x == -1 and (y == numeric_limits<FloatType>::infinity() or y == -numeric_limits<FloatType>::infinity()) ? FloatType(1)
																						: y == -numeric_limits<FloatType>::infinity() ? math::fabs(x) < 1 ? numeric_limits<FloatType>::infinity()
																														  : FloatType(0)
																											      : y == numeric_limits<FloatType>::infinity() ? math::fabs(x) < 1 ? FloatType(0)
																																			       : numeric_limits<FloatType>::infinity()
																																	   : x == -numeric_limits<FloatType>::infinity() ? y < 0 ? math::is_odd(y) ? -FloatType(0)
																																										   : FloatType(0)
																																								 : math::is_odd(y) ? -numeric_limits<FloatType>::infinity()
																																										   : numeric_limits<FloatType>::infinity()
																																							 : x == numeric_limits<FloatType>::infinity() ? y < 0 ? FloatType(0)
																																													      : numeric_limits<FloatType>::infinity()
																																												      : x < 0 and !math::is_integer(y) ? numeric_limits<FloatType>::quiet_NaN()
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	: detail::builtin_pow(x, y)
#else
	: static_cast<FloatType>(detail::pow_impl(static_cast<typename detail::float_compute<FloatType>::type>(x), static_cast<typename detail::float_compute<FloatType>::type>(y)))
#endif
	    ;
}

template <typename ArithmeticType1, typename ArithmeticType2, REQUIRES(std::is_arithmetic<ArithmeticType1>::value and std::is_arithmetic<ArithmeticType2>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr typename detail::float_compute<ArithmeticType1, ArithmeticType2>::type
    pow(ArithmeticType1 x, ArithmeticType2 y)
	SROOK_NOEXCEPT(math::pow(static_cast<typename float_promote<ArithmeticType1>::type>(x), static_cast<typename float_promote<ArithmeticType2>::type>(y)))
{
    typedef typename float_promote<ArithmeticType1, ArithmeticType2>::type type;
    return math::pow(static_cast<type>(x), static_cast<type>(y));
}

} // namespace v1
} // namespace math

using math::pow;

} // namespace srook
#endif
