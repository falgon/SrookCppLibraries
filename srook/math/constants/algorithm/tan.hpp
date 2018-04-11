// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_TAN_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_TAN_HPP

#include <srook/math/constants/algorithm/cos.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/math/constants/algorithm/sin.hpp>
#include <srook/type_traits/is_floating_point.hpp>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE constexpr float builtin_tan(float x) SROOK_NOEXCEPT(__builtin_tanf(x))
{
    return __builtin_tanf(x);
}
SROOK_FORCE_INLINE constexpr double builtin_tan(double x) SROOK_NOEXCEPT(__builtin_tan(x))
{
    return __builtin_tan(x);
}
SROOK_FORCE_INLINE constexpr long double builtin_tan(long double x) SROOK_NOEXCEPT(__builtin_tanl(x))
{
    return __builtin_tanl(x);
}
#endif

} // namespace detail

template <typename FloatType, REQUIRES(is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
constexpr FloatType tan(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
    SROOK_NOEXCEPT(detail::builtin_tan(x))
#else
   SROOK_NOEXCEPT(noexcept(math::fmod(x,FloatType())) and noexcept(math::sin(FloatType())))
#endif
{
    return math::isnan(x) ? x : x >= numeric_limits<FloatType>::infinity() or x <= -numeric_limits<FloatType>::infinity() ? -numeric_limits<FloatType>::quiet_NaN()
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
															  : detail::builtin_tan(x)
#else
															  : x == 0 ? x 
                                                              : srook::math::sin(static_cast<SROOK_DEDUCED_TYPENAME srook::math::detail::float_compute<FloatType>::type>(x)) / srook::math::cos(static_cast<SROOK_DEDUCED_TYPENAME srook::math::detail::float_compute<FloatType>::type>(x))
#endif
	;
}

template <typename IntType, REQUIRES(std::is_integral<IntType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
constexpr double tan(IntType x) SROOK_NOEXCEPT(math::tan(static_cast<double>(x)))
{
    return math::tan(static_cast<double>(x));
}

} // namespace v1
} // namespace math

using math::tan;

} // namespace srook

#endif
