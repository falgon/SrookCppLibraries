// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_FMOD_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_FMOD_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/config/builtin.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {

namespace detail {
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
template <typename T>
SROOK_FORCE_INLINE constexpr T builtin_fmod(T x, T y) SROOK_NOEXCEPT(__builtin_fmod(x, y))
{
    return __builtin_fmod(x, y);
}
#endif

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
inline FloatType constexpr fmod_impl(FloatType x, FloatType y) SROOK_NOEXCEPT_TRUE
{
	return x - static_cast<int>(x / y) * y;
}

} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr FloatType
    fmod(FloatType x, FloatType y)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	SROOK_NOEXCEPT(__builtin_fmod(x, y))
#else
	SROOK_NOEXCEPT_TRUE
#endif
{
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	detail::builtin_fmod(x, y)
#else
	detail::fmod_impl(x, y)
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
    fmod(IntType x, IntType y)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	SROOK_NOEXCEPT(__builtin_fmod(x, y))
#else
	SROOK_NOEXCEPT_TRUE
#endif
{
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	detail::builtin_fmod(static_cast<double>(x), static_cast<double>(y))
#else
	detail::fmod_impl(static_cast<double>(x), static_cast<double>(y))
#endif
	    ;
}

} // namespace v1
} // namespace math

using math::fmod;

} // namespace srook

#endif
