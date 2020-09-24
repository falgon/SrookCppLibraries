// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BIT_HAMMING_HPP
#define INCLUDED_SROOK_BIT_HAMMING_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/bit/algorithm/popcnt.hpp>
#include <srook/algorithm/max.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/limits/numeric_limits.hpp>

SROOK_NESTED_NAMESPACE(srook, bit, algorithm) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T>
struct iec559_wrapper 
    : bool_constant<numeric_limits<T>::is_iec559> {};

} // namespace detail

template <typename Integral>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<is_integral<Integral>::value, SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type>::type
hamming(Integral x, Integral y)
{
    return srook::bit::algorithm::popcnt(x ^ y);
}

template <typename Integral1, typename Integral2>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<is_integral<Integral1>, is_integral<Integral2>>::value, 
    SROOK_DEDUCED_TYPENAME detail::popcnt<srook::algorithm::max(sizeof(Integral1), sizeof(Integral2))>::result_type
>::type
hamming(Integral1 x, Integral2 y)
{
    typedef SROOK_DEDUCED_TYPENAME conditional<sizeof(Integral1) < sizeof(Integral2), Integral2, Integral1>::type type;
    return hamming(static_cast<type>(x), static_cast<type>(y));
}

template <typename FloatType1, typename FloatType2>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<is_floating_point<FloatType1>, is_floating_point<FloatType2>>::value,
    SROOK_DEDUCED_TYPENAME detail::popcnt<srook::algorithm::max(sizeof(FloatType1), sizeof(FloatType2))>::result_type
>::type
hamming(FloatType1 x, FloatType2 y)
{
    typedef SROOK_DEDUCED_TYPENAME conditional<sizeof(FloatType1) < sizeof(FloatType2), FloatType2, FloatType1>::type max_type;
    SROOK_STATIC_ASSERT((sizeof(max_type) > sizeof(double)), "greater than 64 bit is not supported...");
    typedef SROOK_DEDUCED_TYPENAME 
        conditional<
            type_traits::detail::Land<detail::iec559_wrapper<max_type>, bool_constant<sizeof(max_type) == sizeof(srook::uint64_t)>>::value, 
            srook::uint64_t,
            SROOK_DEDUCED_TYPENAME conditional<
                type_traits::detail::Land<detail::iec559_wrapper<max_type>, bool_constant<sizeof(max_type) == sizeof(srook::uint32_t)>>::value,
                srook::uint32_t,
                srook::uint64_t
            >::type
        >::type deducted_type;
    return hamming(static_cast<deducted_type>(x), static_cast<deducted_type>(y));
}

template <class Pointer1, class Pointer2>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(std::uintptr_t)>::result_type
hamming(Pointer1* x, Pointer2* y)
{
    return hamming(reinterpret_cast<std::uintptr_t>(x), reinterpret_cast<std::uintptr_t>(y));
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_NULLPTR_T hamming(SROOK_NULLPTR_T x) { return x; }

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, bit, srook)

#endif
