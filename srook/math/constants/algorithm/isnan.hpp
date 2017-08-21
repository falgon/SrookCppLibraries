// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGOITHM_IS_NAN_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGOITHM_IS_NAN_HPP
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/math/config/builtin.hpp>

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
#if SROOK_CPP_RVALUE_REFERENCES
#include <utility>
#endif
namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

template <typename FloatType>
SROOK_FORCE_INLINE
#if SROOK_CPP_CONSTEXPR
    constexpr
#endif
    bool
    builtin_isnan(
	FloatType
#if SROOK_CPP_RVALUE_REFERENCES
	    &&
#endif
		x)
{
    return __builtin_isnan(
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
} // namespace v1
} // namespace math
} // namespace srook

#endif

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

#include <srook/config/require.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {

template <typename FloatType, REQUIRES(std::is_floating_point<typename std::decay<FloatType>::type>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr bool
    isnan(FloatType &&x)
{
#include <srook/config/disable_warnings/push/Wfloat_equal.hpp>
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	detail::builtin_isnan(std::forward<FloatType>(x))
#else
	!(x == x)
#endif
	    ;
#include <srook/config/disable_warnings/pop.hpp>
}

template <typename IntType, REQUIRES(std::is_integral<typename std::decay<IntType>::type>::value)>
SROOK_FORCE_INLINE constexpr bool isnan(IntType &&)
{
    return false;
}

} // namespace v1
} // namespace math

using math::isnan;

} // namespace srook

#else

namespace srook {
namespace math {
namespace detail {

template <typename FloatType>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr bool
    isnan(FloatType x)
{
#include <srook/config/disable_warnings/push/Wfloat_equal.hpp>
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	detail::builtin_isnan(x)
#else
	!(x == x)
#endif
	    ;
#include <srook/config/disable_warnings/pop.hpp>
}

} // namespace detail
} // namespace math

using math::isnan;

} // namespace srook
#endif
#endif
