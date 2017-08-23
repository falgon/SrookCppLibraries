// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_ISINITIE_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_ISINITIE_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/isinf.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {

namespace detail {

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
template <typename FloatType>
SROOK_FORCE_INLINE constexpr bool builtin_isfinite(FloatType x) SROOK_NOEXCEPT(__builtin_isfinite(x))
{
    return __builtin_isfinite(x);
}

#endif
}

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE 
#else
inline
#endif
constexpr bool isfinite(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
    SROOK_NOEXCEPT(detail::builtin_isfinite(x))
#else
    SROOK_NOEXCEPT(!(math::isnan(x) or math::isinf(x)))
#endif
{
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	detail::builtin_isfinite(x)
#else
	!(math::isnan(x) or math::isinf(x))
#endif
	    ;
}

template <typename IntType, REQUIRES(std::is_integral<IntType>::value)>
SROOK_FORCE_INLINE constexpr bool isfinite(IntType) SROOK_NOEXCEPT_TRUE
{
    return true;
}

} // namespace v1
} // namespace math

using math::isfinite;

} // namespace srook

#endif
