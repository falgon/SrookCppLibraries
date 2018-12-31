// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_APPROXIMATE_RECIPROCAL_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_APPROXIMATE_RECIPROCAL_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/disable_if.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/utility/move.hpp>
#include <srook/cstdint.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <type_traits>

SROOK_NESTED_NAMESPACE(srook, math, approximate) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

// Using boost::variant or std::variant(since C++17) with this implementation is overkill
template <class F, class I>
struct ud_proxy {
    union { F fp; I i; };
    SROOK_CONSTEXPR ud_proxy(type_constant<F>, F v)
        : fp(srook::move(v)) {}
    SROOK_CONSTEXPR ud_proxy(type_constant<I>, I v)
        : i(srook::move(v)) {}
    template <class T>
    SROOK_CONSTEXPR ud_proxy(T v) 
        : ud_proxy(type_constant<T>(), srook::move(v)) {}
};

template <std::size_t>
struct reciprocal_traits;

template <>
struct reciprocal_traits<4> {
    typedef float float_type;
    typedef srook::uint32_t integer_type;
    SROOK_ST_ASSERT(numeric_limits<float_type>::is_iec559);
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR integer_type mn = 0xbe6eb3beU;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME std::underlying_type<srook::byte>::type abyte = 1;
    typedef ud_proxy<float_type, integer_type> union_type;
};

template <>
struct reciprocal_traits<8> {
    typedef double float_type;
    typedef srook::uint64_t integer_type;
    SROOK_ST_ASSERT(numeric_limits<float_type>::is_iec559);
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR integer_type mn = 0xbfcdd6a18f6a6f52ULL;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME std::underlying_type<srook::byte>::type abyte = 1;
    typedef ud_proxy<float_type, integer_type> union_type;
};

} // namespace detail

// ref: https://en.wikipedia.org/wiki/Fast_inverse_square_root
template <class T>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
enable_if<is_floating_point<T>::value, SROOK_DEDUCED_TYPENAME detail::reciprocal_traits<sizeof(T)>::float_type>::type
reciprocal(T val)
{
    typedef detail::reciprocal_traits<sizeof(T)> traits_type;
    SROOK_DEDUCED_TYPENAME traits_type::union_type u(val);
    u.i = (traits_type::mn - u.i) >> traits_type::abyte;
    return u.fp *= u.fp;
}

SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
detail::reciprocal_traits<sizeof(srook::uint64_t)>::float_type
reciprocal(srook::uint64_t val)
{
    typedef detail::reciprocal_traits<sizeof(srook::uint64_t)> traits_type;
    SROOK_DEDUCED_TYPENAME traits_type::union_type u(static_cast<double>(val * val));
    u.i = (traits_type::mn - u.i) >> traits_type::abyte;
    return u.fp;
}

template <class T>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
disable_if<type_traits::detail::Lor<is_floating_point<T>, is_same<T, srook::uint64_t>, is_pointer<T>>::value, srook::uint64_t>::type
reciprocal(T val)
{
    return reciprocal(static_cast<srook::uint64_t>(val));
}

#ifdef SROOK_HAS_INTPTR_T
template <class P>
SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uintptr_t reciprocal(P* x)
{
    return reciprocal(reinterpret_cast<srook::uintptr_t>(x));
}
#endif

SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME conditional<sizeof(SROOK_NULLPTR_T) == 4, float, double>::type
reciprocal(SROOK_NULLPTR_T)
{
    return numeric_limits<SROOK_DEDUCED_TYPENAME conditional<sizeof(SROOK_NULLPTR_T) == 4, float, double>::type>::quiet_NaN();
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(approximate, math, srook)
#endif
#endif
