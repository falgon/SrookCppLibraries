// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_GCD_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_GCD_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cstdint.hpp>
#include <srook/type_traits.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/math/config/builtin.hpp>
#include <type_traits>
#if SROOK_HAS_INCLUDE(<boost/multiprecision/cpp_int.hpp>)
#   include <boost/multiprecision/cpp_int.hpp>
#endif

SROOK_NESTED_NAMESPACE(srook, math) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t> struct floating_point_to_integral;
template <>
struct floating_point_to_integral<4> : public type_constant<srook::int32_t> {};
template <>
struct floating_point_to_integral<8> : public type_constant<srook::int64_t> {};
#if defined(__GNUC__) && defined(__x86_64__) && SROOK_HAS_BOOST_MULTIPRECISION_CPP_INT_HPP
template <>
struct floating_point_to_integral<16> : public type_constant<boost::multiprecision::int128_t> {};
#endif

template <bool, bool, typename, typename> struct gcd_traits;
template <typename T, typename U>
struct gcd_traits<true, true, T, U> {
    typedef SROOK_DEDUCED_TYPENAME floating_point_to_integral<sizeof(SROOK_DEDUCED_TYPENAME std::common_type<T, U>::type)>::type result_type;
};

template <class IntegralType>
SROOK_CONSTEXPR IntegralType gcd_impl(IntegralType x, IntegralType y)
{
    return !y ? x : gcd_impl(y, x % y);
}

template <class FloatType>
SROOK_CONSTEXPR bool is_valid(FloatType x)
{
    return !isnan(x) && x < numeric_limits<FloatType>::infinity() && x > -numeric_limits<FloatType>::infinity();
}

} // namespace detail

template <typename IntegralType1, typename IntegralType2>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<type_traits::detail::Land<is_integral<IntegralType1>, is_integral<IntegralType2>>::value, SROOK_DEDUCED_TYPENAME std::common_type<IntegralType1, IntegralType2>::type>::type
gcd(IntegralType1 x, IntegralType2 y)
{
    typedef SROOK_DEDUCED_TYPENAME std::common_type<IntegralType1, IntegralType2>::type result_type;
    return detail::gcd_impl(static_cast<result_type>(x), static_cast<result_type>(y));
}

template <typename FloatType1, typename FloatType2>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<is_floating_point<FloatType1>, is_floating_point<FloatType2>>::value, 
    SROOK_DEDUCED_TYPENAME detail::gcd_traits<numeric_limits<FloatType1>::is_iec559, numeric_limits<FloatType2>::is_iec559, FloatType1, FloatType2>::result_type
>::type
gcd(FloatType1 x, FloatType2 y)
{
    typedef SROOK_DEDUCED_TYPENAME detail::gcd_traits<numeric_limits<FloatType1>::is_iec559, numeric_limits<FloatType2>::is_iec559, FloatType1, FloatType2>::result_type result_type;
    return detail::is_valid(x) && detail::is_valid(y) ? gcd(static_cast<result_type>(x), static_cast<result_type>(y)) : 0;
}

template <typename IntegralType, typename FloatType>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<is_integral<IntegralType>, is_floating_point<FloatType>>::value,
    SROOK_DEDUCED_TYPENAME detail::gcd_traits<numeric_limits<FloatType>::is_iec559, true, FloatType, IntegralType>::result_type
>::type
gcd(IntegralType x, FloatType y)
{
    typedef SROOK_DEDUCED_TYPENAME detail::gcd_traits<numeric_limits<FloatType>::is_iec559, true, FloatType, IntegralType>::result_type result_type;
    return detail::is_valid(y) ? gcd(static_cast<result_type>(x), static_cast<result_type>(y)) : 0;
}

template <typename IntegralType, typename FloatType>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<is_integral<IntegralType>, is_floating_point<FloatType>>::value,
    SROOK_DEDUCED_TYPENAME detail::gcd_traits<numeric_limits<FloatType>::is_iec559, true, FloatType, IntegralType>::result_type
>::type
gcd(FloatType x, IntegralType y)
{
    return gcd(y, x);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(math, srook)

#endif
