// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGOITHM_IS_INF_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGOITHM_IS_INF_HPP
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/math/config/builtin.hpp>

#if SROOK_USE_BUILTIN_CMATH_FUNCTION
#if SROOK_CPP_RVALUE_REFERENCES
#	include<utility>
#endif
namespace srook {
namespace math {
inline namespace v1{
namespace detail {

template <typename FloatType>
SROOK_FORCE_INLINE
#if SROOK_CPP_CONSTEXPR
    constexpr
#endif
    bool
    builtin_isinf(
	FloatType
#if SROOK_CPP_RVALUE_REFERENCES
	    &&
#endif
		x)
{
	return __builtin_isinf(
#if SROOK_CPP_RVALUE_REFERENCES
			std::forward<FloatType>(
#endif
				x
#if SROOK_CPP_RVALUE_REFERENCES
			)
#endif
			);
}

} // namespace detail
} // inline namespace v1
} // namespace math
} // namespace srook

#endif

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

#include <limits>
#include <srook/config/require.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {

template <typename FloatType, REQUIRES(std::is_floating_point<typename std::decay<FloatType>::type>::value)>
SROOK_FORCE_INLINE constexpr bool isinf(FloatType &&x)
{
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION
	detail::builtin_isinf(std::forward<FloatType>(x))
#else
	x >= std::numeric_limits<FloatType>::infinity() or x <= -std::numeric_limits<FloatType>::infinity() // to silence warning
#endif
	    ;
}

template <typename IntType, REQUIRES(std::is_integral<typename std::decay<IntType>::type>::value)>
SROOK_FORCE_INLINE constexpr bool isinf(IntType &&)
{
    return false;
}

} // namespace v1
} // namespace math

using math::isinf;

} // namespace srook

#else

#if SROOK_USE_BUILTIN_CMATH_FUNCTION
#include <srook/limits/numeric_limits.hpp>
#endif

namespace srook {
namespace math {
namespace detail {

template <typename FloatType>
SROOK_FORCE_INLINE constexpr bool isinf(FloatType x)
{
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION
	detail::builtin_isinf(x)
#else
	x >= srook::numeric_limits<FloatType>::infinity() or x <= -srook::numeric_limits<FloatType>::infinity() // to silence warning
#endif
	    ;
}

} // namespace detail
} // namespace math

using math::isinf;

} // namespace srook
#endif
#endif
