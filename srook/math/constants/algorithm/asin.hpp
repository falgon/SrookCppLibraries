// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_ASIN_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_ASIN_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/math/constants/algorithm/abs.hpp>
#include <srook/math/constants/algorithm/pow.hpp>
#include <srook/math/detail/feq.hpp>
#include <srook/math/constants/pi.hpp>

SROOK_NESTED_NAMESPACE(srook, math) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <typename T>
SROOK_CONSTEXPR T asin_impl(T x, T s, int n, T t)
{
    return feq(s, s + t * static_cast<T>(n) / (n + 2)) ? s : asin_impl(x, s + t * static_cast<T>(n) / (n + 2), n + 2, t * pow(x, 2) * static_cast<T>(n) / (n + 3));
}

} // namespace detail

template <typename FloatType>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_floating_point<FloatType>::value, FloatType>::type 
asin(FloatType x)
{
    typedef srook::math::PI<FloatType> pi_type;
    return 
        x == FloatType(-1) ? -pi_type::half()
        : x == FloatType(1) ? pi_type::half()
        : x > FloatType(-1) && x < FloatType(1) ? detail::asin_impl(x, x, 1, pow(x, 3) / FloatType(2)) : numeric_limits<FloatType>::quiet_NaN();
}

template <typename IntegralType>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_integral<IntegralType>::value, IntegralType>::type
asin(IntegralType x)
{
    return asin(static_cast<double>(x));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(math, srook)

#endif
