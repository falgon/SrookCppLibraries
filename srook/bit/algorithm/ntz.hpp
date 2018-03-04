// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BIT_COUNT_TRAILING_ZEROS_HPP
#define INCLUDED_SROOK_BIT_COUNT_TRAILING_ZEROS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#   if SROOK_ARCH_IS_X86_64
#       include <intrin.h>
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#if ((defined(_MSC_VER) && SROOK_ARCH_IS_X86_64) || defined(__GNUC__))
#   define SROOK_ASM_CONSTEXPR SROOK_CONSTEXPR
#else
#   define SROOK_ASM_CONSTEXPR
#endif

#include <srook/bit/algorithm/popcnt.hpp>
#include <srook/cstdint.hpp>
#include <srook/type_traits.hpp>
#include <type_traits>
#include <cassert>

SROOK_NESTED_NAMESPACE(srook, bit, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

// De Bruijn sequence
template <class> struct magic;

template <>
struct magic<srook::uint8_t> : public integral_constant<unsigned int, 0x1dU> {
    static SROOK_CONSTEXPR_OR_CONST int shift = 4;
    static SROOK_CONSTEXPR_OR_CONST int table[] = { 8, 0, -1, 1, 6, -1, -1, 2, 7, -1, 5, -1, -1, 4, 3 };
};

template <>
struct magic<srook::uint16_t> : public integral_constant<unsigned int, 0x0d2dU> {
    static SROOK_CONSTEXPR_OR_CONST int shift = 11;
    static SROOK_CONSTEXPR_OR_CONST int table[] = {
        16, 0, -1, 1, -1, 8, -1, 2, 14, -1, -1, 9, -1, 11, -1, 3,
        15, -1, 7, -1, 13, -1, 10, -1, -1, 6, 12, -1, 5, -1, 4 
    };
};

template <>
struct magic<srook::uint32_t> : public integral_constant<srook::uint32_t, 0x07c56e99U> {
    static SROOK_CONSTEXPR_OR_CONST int shift = 26;
    static SROOK_CONSTEXPR_OR_CONST int table[] = {
        32, 0, -1, 1, -1, 10, -1, 2, 29, -1, 11, -1, 25, -1, -1, 3,
        30, -1, -1, 23, -1, 12, 14, -1, -1, 26, -1, 16, -1, 19, -1, 4,
        31, -1, 9, -1, 28, -1, 24, -1, -1, 22, -1, 13, -1, 15, 18, -1,
        -1, 8, 27, -1, 21, -1, -1, 17, 7, -1, 20, -1, 6, -1, 5
    };
};

template <>
struct magic<srook::uint64_t> : public integral_constant<srook::uint64_t, 0x03F0A933ADCBD8D1ULL> {
    static SROOK_CONSTEXPR_OR_CONST int shift = 57;
    static SROOK_CONSTEXPR_OR_CONST int table[] = {
        64,  0, -1, 1, -1, 12, -1, 2, 60, -1, 13, -1, -1, 53, -1, 3,
        61, -1, -1, 21, -1, 14, -1, 42, -1, 24, 54, -1, -1, 28, -1, 4,
        62, -1, 58, -1, 19, -1, 22, -1, -1, 17, 15, -1, -1, 33, -1, 43,
        -1, 50, -1, 25, 55, -1, -1, 35, -1, 38, 29, -1, -1, 45, -1, 5,
        63, -1, 11, -1, 59, -1, 52, -1, -1, 20, -1, 41, 23, -1, 27, -1,
        -1, 57, 18, -1, 16, -1, 32, -1, 49, -1, -1, 34, 37, -1, 44, -1,
        -1, 10, -1, 51, -1, 40, -1, 26, 56, -1, -1, 31, 48, -1, 36, -1,
        9, -1, 39, -1, -1, 30, 47, -1, 8, -1, -1, 46, 7, -1, 6
    };
};

template <class T>
struct ntz_impl {
    typedef T result_type;
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type x)
    {
        return magic<result_type>::table[static_cast<result_type>(static_cast<result_type>(x & -x) * magic<result_type>::value) >> magic<result_type>::shift];
    }
};

template <std::size_t>
struct ntz;

template <>
struct ntz<1> {
    typedef SROOK_DEDUCED_TYPENAME ntz_impl<srook::uint8_t>::result_type result_type;
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type x)
    {
        return ntz_impl<result_type>::apply(x);
    }
};

template <>
struct ntz<2> {
    typedef SROOK_DEDUCED_TYPENAME ntz_impl<srook::uint16_t>::result_type result_type;
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type x)
    {
        return ntz_impl<result_type>::apply(x);
    }
};

template <>
struct ntz<4> {
    typedef SROOK_DEDUCED_TYPENAME ntz_impl<srook::uint32_t>::result_type result_type;
    static SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR result_type apply(result_type x)
    {
#if defined(_MSC_VER) && SROOK_ARCH_IS_X86_64
        result_type r;
        return _BitScanForward(&r, x) ? r : 64;
#elif defined(__GNUC__)
        return x ? __builtin_ctz(x) : 64;
#elif SROOK_ARCH_IS_X86_64 || SROOK_ARCH_I386
        asm ("bsfl %1,%0" : "=r"(x) : "r"(x));
        return x;
#else
        return ntz_impl<result_type>::apply(x);
#endif
    }
};

template <>
struct ntz<8> {
    typedef SROOK_DEDUCED_TYPENAME ntz_impl<srook::uint32_t>::result_type result_type;
    static SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR result_type apply(result_type x)
    {
#if defined(_MSC_VER) && SROOK_ARCH_IS_X86_64
        result_type r;
        return _BitScanForward64(&r, x) ? r : 64;
#elif defined(__GNUC__)
        return x ? __builtin_ctzl(x) : 64;
#elif SROOK_ARCH_IS_X86_64 || SROOK_ARCH_I386 
        asm ("bsfq %1, %0" : "=r"(x) : "r"(x));
        return x;
#else
        return ntz_impl<result_type>::apply(x);
#endif
    }
};

} // namespace detail


template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<std::is_unsigned<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR
SROOK_DEDUCED_TYPENAME detail::ntz<sizeof(Integral)>::result_type ntz(Integral x)
{
    return detail::ntz<sizeof(Integral)>::apply(x);
}

template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<std::is_signed<Integral>, is_integral<Integral>>::value)>
inline SROOK_ASM_CONSTEXPR
SROOK_DEDUCED_TYPENAME detail::ntz<sizeof(SROOK_DEDUCED_TYPENAME std::make_unsigned<Integral>::type)>::result_type ntz(Integral x)
{
    return ntz(static_cast<SROOK_DEDUCED_TYPENAME std::make_unsigned<Integral>::type>(x));
}

template <class Pointer>
inline SROOK_ASM_CONSTEXPR
SROOK_DEDUCED_TYPENAME detail::ntz<sizeof(std::uintptr_t)>::result_type ntz(Pointer* ptr)
{
    return ntz(reinterpret_cast<std::uintptr_t>(ptr));
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR bool ntz(bool b)
{
    return !b;
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR std::nullptr_t ntz(std::nullptr_t x)
{
    return x;
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, bit, srook)

#if defined(__clang__)
#   pragma clang  diagnostic pop
#endif

#undef SROOK_ASM_CONSTEXPR
#endif
#endif
