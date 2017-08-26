#ifndef INCLUDED_SROOK_MATH_CONSTANT_ALGORITHM_SIGN_BIT_HPP
#define INCLUDED_SROOK_MATH_CONSTANT_ALGORITHM_SIGN_BIT_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/copysign.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {

namespace detail {

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
template <class FloatType>
SROOK_FORCE_INLINE constexpr bool builtin_signbit(FloatType x) SROOK_NOEXCEPT(__builtin_signbit(x))
{
    return __builtin_signbit(x);
}
#endif

} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
    constexpr bool
    signbit(FloatType x)
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	SROOK_NOEXCEPT(detail::builtin_signbit(x))
#else
	SROOK_NOEXCEPT(math::copysign(FloatType(1), x) < FloatType(0))
#endif
{
    return
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
	detail::builtin_signbit(x)
#else
	math::copysign(FloatType(1), x) < FloatType(0)
#endif
	    ;
}

template <typename IntType, REQUIRES(std::is_integral<IntType>::value)>
SROOK_FORCE_INLINE constexpr bool signbit(IntType x) SROOK_NOEXCEPT_TRUE
{
    return x < 0;
}

} // namespace v1
} // namespace math

using math::signbit;

} // namespace srook
#endif
