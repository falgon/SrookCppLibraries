#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_HYPOT_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_HYPOT_HPP

#include<srook/math/config/builtin.hpp>
#include<srook/config/attribute/force_inline.hpp>
#include<srook/config/require.hpp>
#include<srook/config/noexcept_detection.hpp>
#include<srook/limits/numeric_limits.hpp>
#include<srook/math/detail/float_compute.hpp>
#include<srook/math/constants/algorithm/fabs.hpp>
#include<srook/math/constants/algorithm/isnan.hpp>
#include<srook/type_traits/float_promote.hpp>
#include<srook/math/constants/algorithm/sqrt.hpp>
#include<srook/math/constants/algorithm/signbit.hpp>

namespace srook{
namespace math{
inline namespace v1{
namespace detail{

#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE constexpr float builtin_hypot(float x,float y) SROOK_NOEXCEPT(__builtin_hypof(x,y))
{
	return __builtin_hypotf(x,y);
}
SROOK_FORCE_INLINE constexpr double builtin_hypot(double x,double y) SROOK_NOEXCEPT(__builtin_hypot(x,y))
{
	return __builtin_hypot(x,y);
}
SROOK_FORCE_INLINE constexpr long double builtin_hypot(long double x,long double y) SROOK_NOEXCEPT(__builtin_hypotl(x,y))
{
	return __builtin_hypotl(x,y);
}
#endif

template<typename T>
SROOK_FORCE_INLINE constexpr T hypot_impl2(T t,T w)
{
	return t * math::sqrt(T(1) + w * w);
}
template<typename T>
SROOK_FORCE_INLINE constexpr T hypot_impl1(T x,T y)
{
	return x < y ? hypot_impl2(y,x/y) : hypot_impl2(x,y/x);
}
template<typename T>
SROOK_FORCE_INLINE constexpr T hypot_impl(T x,T y)
{
	return hypot_impl1(math::fabs(x),math::fabs(y));
}

} // namespace detail

template<typename FloatType,REQUIRES(std::is_floating_point<FloatType>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
constexpr FloatType hypot(FloatType x,FloatType y)
{
	return y == numeric_limits<FloatType>::infinity() || y == -numeric_limits<FloatType>::infinity() ? numeric_limits<FloatType>::infinity() : x == numeric_limits<FloatType>::infinity() || x == -numeric_limits<FloatType>::infinity() ? numeric_limits<FloatType>::infinity() : math::isnan(y) ? y : math::isnan(x) ? x
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
				:detail::builtin_hypot(x,y)
#else
				:y == 0 ? math::fabs(x)
				:x == 0 ? math::fabs(y)
				: static_cast<FloatType>(detail::hypot_impl(static_cast<typename detail::float_compute<FloatType>::type>(x),static_cast<typename detail::float_compute<FloatType>::type(y)))
#endif
				;
}

template<typename ArithmeticType1,typename ArithmeticType2,REQUIRES(std::is_arithmetic<ArithmeticType1>::value and std::is_arithmetic<ArithmeticType2>::value)>
#if SROOK_USE_BUILTIN_CMATH_FUNCTION && SROOK_BUILTIN_CMATH_FUNCTION_IS_DEFINED_CONSTEXPR
SROOK_FORCE_INLINE
#else
inline
#endif
constexpr typename float_promote<ArithmeticType1,ArithmeticType2>::type hypot(ArithmeticType1 x,ArithmeticType2 y)
{
	typedef typename float_promote<ArithmeticType1,ArithmeticType2>::type type;
	return math::hypot(static_cast<type>(x),static_cast<type>(y));
}

} // inline namespace v1
}
}

#endif
