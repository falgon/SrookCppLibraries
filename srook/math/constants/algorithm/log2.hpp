// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_LOG2_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_LOG2_HPP

#include <srook/math/constants/algorithm/log.hpp>
#include <srook/math/constants/ln.hpp>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE SROOK_CONSTEXPR float builtin_log2(float x) SROOK_NOEXCEPT(__builtin_log2f(x))
{
    return __builtin_log2f(x);
}
SROOK_FORCE_INLINE SROOK_CONSTEXPR double builtin_log2(double x) SROOK_NOEXCEPT(__builtin_log2(x))
{
    return __builtin_log2(x);
}
SROOK_FORCE_INLINE SROOK_CONSTEXPR long double builtin_log2(long double x) SROOK_NOEXCEPT(__builtin_log2l(x))
{
    return __builtin_log2l(x);
}
#endif

template <typename T>
inline SROOK_CONSTEXPR T log2_impl(T x) SROOK_NOEXCEPT(detail::log2_impl1(T(1) / x))
{
    return srook::math::log(x) / srook::math::ln_two<T>();
}

} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
SROOK_CONSTEXPR FloatType log2(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
    SROOK_NOEXCEPT(detail::builtin_log2(x))
#else
    SROOK_NOEXCEPT(detail::log2_impl(static_cast<typename detail::float_compute<FloatType>::type>(x)))
#endif
{
    return math::isnan(x) ? x 
        : x == 0 ? -numeric_limits<FloatType>::infinity() 
        : x >= numeric_limits<FloatType>::infinity() ? numeric_limits<FloatType>::infinity() 
        : x < 0 ? numeric_limits<FloatType>::quiet_NaN()
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
        : detail::builtin_log2(x)
#else
        : x == 1 ? FloatType(0)
        : static_cast<FloatType>(detail::log2_impl(static_cast<typename detail::float_compute<FloatType>::type>(x)))
#endif
	;
}

template <typename IntType, REQUIRES(std::is_integral<IntType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
SROOK_CONSTEXPR double log2(IntType x) SROOK_NOEXCEPT(math::log2(static_cast<double>(x)))
{
    return math::log2(static_cast<double>(x));
}

} // namespace v1
} // namespace math

using math::log2;

} // namespace srook

#endif
