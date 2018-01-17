// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_GEOMETORY_MIN_AREA_POLYGON_HPP
#define INCLUDED_SROOK_MATH_GEOMETORY_MIN_AREA_POLYGON_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#ifdef SROOK_CONFIG_DISABLE_BUILTIN_CMATH_FUNCTION
#   define SROOK_NO_UNDEF_CONFIG_DBCF
#   undef SROOK_CONFIG_DISABLE_BUILTIN_CMATH_FUNCTION
#endif

#define SROOK_CONFIG_DISABLE_BUILTIN_CMATH_FUNCTION 1

#include <srook/config.hpp>
#include <srook/math/constants/pi.hpp>
#include <srook/math/constants/algorithm/gcd.hpp>
#include <srook/math/constants/algorithm/sqrt.hpp>
#include <srook/math/constants/algorithm/acos.hpp>
#include <srook/math/constants/algorithm/sin.hpp>
#include <srook/math/constants/algorithm/pow.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/tmpl/vt/size_eq.hpp>

SROOK_NESTED_NAMESPACE(srook, math, geometory) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <typename F>
SROOK_CONSTEXPR bool map_is_valid(F f)
{
    return !(isnan(f) || numeric_limits<F>::infinity() <= f || -numeric_limits<F>::infinity() >= f);
}

template <typename F, typename... FloatType>
SROOK_CONSTEXPR bool map_is_valid(F f, FloatType... fs)
{
    return map_is_valid(f) ? map_is_valid(fs...) : false;
}

template <typename FloatType>
SROOK_CONSTEXPR FloatType map_gcd(FloatType x, FloatType y)
{
    return fabs(y) < 1e-4 ? x : map_gcd(y, fmod(x, y));
}

template <typename FloatType>
SROOK_CONSTEXPR FloatType length_of_the_sides(FloatType x1, FloatType x2, FloatType y1, FloatType y2)
{
    return sqrt(pow((x1 - x2), 2) + pow(y1 - y2, 2));
}

template <typename FloatType>
SROOK_CONSTEXPR FloatType map_area_triangle(FloatType semiperimeter, FloatType a, FloatType b, FloatType c)
{
    return sqrt(semiperimeter * (semiperimeter - a) * (semiperimeter - b) * (semiperimeter - c));
}

template <typename FloatType>
SROOK_CONSTEXPR FloatType map_radius(FloatType area_triangle, FloatType a, FloatType b, FloatType c)
{
    return (a * b * c) / (4 * area_triangle);
}

template <typename FloatType>
SROOK_CONSTEXPR FloatType map_semiperimeter(FloatType a, FloatType b, FloatType c)
{
    return (a + b + c) / 2;
}

template <typename FloatType>
SROOK_CONSTEXPR FloatType map_angle(FloatType a, FloatType b, FloatType c)
{
    return acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b));
}

template <typename FloatType>
class min_area_polygon_calc {
public:
    SROOK_CONSTEXPR min_area_polygon_calc(FloatType x1, FloatType y1, FloatType x2, FloatType y2, FloatType x3, FloatType y3)
        : a_(detail::length_of_the_sides(x2, x3, y2, y3)),
        b_(detail::length_of_the_sides(x1, x3, y1, y3)), 
        c_(detail::length_of_the_sides(x1, x2, y1, y2)),
        radius_((a_ * b_ * c_) / (4 * detail::map_area_triangle(detail::map_semiperimeter(a_, b_, c_), a_, b_, c_))),
        n_(PI<FloatType>::value() / static_cast<FloatType>(detail::map_gcd(detail::map_gcd(detail::map_angle(b_, c_, a_), detail::map_angle(a_, c_, b_)), detail::map_angle(b_, a_, c_))))
    {}
    SROOK_CONSTEXPR FloatType operator()() const
    {
        return (n_ * pow(radius_, 2) * sin((2 * PI<FloatType>::value()) / n_)) / 2;
    }
private:
    FloatType a_, b_, c_, radius_, n_;
};

} // namespace detail

template <typename FloatType>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_floating_point<FloatType>::value, FloatType>::type
min_area_polygon(FloatType&& x1, FloatType&& y1, FloatType&& x2, FloatType&& y2, FloatType&& x3, FloatType&& y3)
{
    return 
        detail::map_is_valid(x1, y1, x2, y2, x3, y3) ? 
        detail::min_area_polygon_calc<SROOK_DEDUCED_TYPENAME decay<FloatType>::type>(
                srook::forward<FloatType>(x1), 
                srook::forward<FloatType>(y1), 
                srook::forward<FloatType>(x2), 
                srook::forward<FloatType>(y2), 
                srook::forward<FloatType>(x3), 
                srook::forward<FloatType>(y3)
        )()
        : numeric_limits<FloatType>::quiet_NaN();
}

template <typename IntegralType>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_integral<IntegralType>::value, IntegralType>::type
min_area_polygon(IntegralType x1, IntegralType y1, IntegralType x2, IntegralType y2, IntegralType x3, IntegralType y3)
{
    typedef double type;
    return min_area_polygon(static_cast<type>(x1), static_cast<type>(y1), static_cast<type>(x2), static_cast<type>(y2), static_cast<type>(x3), static_cast<type>(y3));
}

template <typename... Ts>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<type_traits::detail::Land<type_traits::detail::Land<is_arithmetic<Ts>...>, tmpl::vt::size_eq<6, Ts...>>::value, double>::type
min_area_polygon(Ts&&... ts)
{
    typedef SROOK_DEDUCED_TYPENAME std::common_type<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>::type type;
    return min_area_polygon(static_cast<type>(ts)...);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(geometory, math, srook)

#ifndef SROOK_NO_UNDEF_CONFIG_DBCF
#   undef SROOK_CONFIG_DISABLE_BUILTIN_CMATH_FUNCTION
#endif

#endif
