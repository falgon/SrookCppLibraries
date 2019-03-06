// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_ABS_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_ABS_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/math/config/builtin.hpp>
#include <type_traits>

//#if !SROOK_USE_BUILTIN_CMATH_FUNCTION or !SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
#include <srook/math/constants/algorithm/fabs.hpp>
//#endif

namespace srook {
namespace math {
inline namespace v1 {

template <typename ArithmeticType, REQUIRES(std::is_arithmetic<ArithmeticType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr ArithmeticType
    abs(ArithmeticType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	SROOK_NOEXCEPT(__builtin_abs(x))
#else
	SROOK_NOEXCEPT(math::fabs(x))
#endif
{
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	__builtin_abs(x)
#else
	static_cast<ArithmeticType>(math::fabs(x))
#endif
	    ;
}

} // namespace v1
} // namespace math

using math::abs;

} // namespace srook

#endif
