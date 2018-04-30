// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BIT_ALGORITHM_MOST_SINGNIFICANT_BIT_HPP
#define INCLUDED_SROOK_BIT_ALGORITHM_MOST_SINGNIFICANT_BIT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config/compiler/msvc/includes/intrin.h>
#include <srook/bit/algorithm/popcnt.hpp>
#include <srook/cstring/memcpy.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/limits/numeric_limits.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#if ((defined(_MSC_VER) && SROOK_ARCH_IS_X86_64) || defined(__GNUC__))
#   define SROOK_ASM_CONSTEXPR SROOK_CONSTEXPR
#else
#   define SROOK_ASM_CONSTEXPR
#endif
#if defined(_MSC_VER) || defined(__GNUC__) || defined(__ARMCC_VERSION)
#   define SROOK_MSB_HAS_COMPILER_INTRINSIC 1
#endif

SROOK_NESTED_NAMESPACE(srook, bit, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t current, std::size_t end>
struct msb_impl {
    template <class Integral>
    static SROOK_CONSTEXPR Integral apply(Integral n) SROOK_NOEXCEPT_TRUE
    {
        return msb_impl<(current << 1), end>::apply(n | (n >> current));
    }
};

template <std::size_t end>
struct msb_impl<end, end> {
    template <class Integral>
    static SROOK_CONSTEXPR Integral apply(Integral n) SROOK_NOEXCEPT_TRUE
    {
        return n | (n >> end);
    }
};

template <class Integral>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type 
do_msb(Integral x)
{
    SROOK_STATIC_ASSERT(sizeof(Integral) % 2 == 0, "The Integral type must be an even bit size.");
    SROOK_STATIC_ASSERT(CHAR_BIT == 8, "CHAR_BIT must be 8");
    return !x ? x : srook::bit::algorithm::popcnt(msb_impl<1, ((sizeof(Integral) * CHAR_BIT) >> 1)>::apply(x)) - 1;
}

#ifdef SROOK_MSB_HAS_COMPILER_INTRINSIC
template <std::size_t>
struct builtin_bitscan {
    template <class Integral>
    static SROOK_CONSTEXPR Integral apply(Integral n) SROOK_NOEXCEPT_TRUE
    {
        return do_msb(srook::move(n));
    }
};

template <std::size_t>
struct builtin_bitscan;

#ifdef __ARMCC_VERSION
template <>
struct builtin_bitscan<1> {
    template <class Integral>
    static SROOK_CONSTEXPR Integral apply(Integral n) SROOK_NOEXCEPT_TRUE
    {
        return 7 - __clz(srook::move(n));
    }
};
#endif

template <>
struct builtin_bitscan<4> {
    template <class Integral>
    static SROOK_CXX14_CONSTEXPR Integral apply(Integral n) SROOK_NOEXCEPT_TRUE
    {
#ifdef _MSC_VER
        Integral result;
        return _BitScanReverse(&result, n) ? result : n;
#else
        return 31 - __builtin_clz(srook::move(n));
#endif
    }
};

template <>
struct builtin_bitscan<8> {
    template <class Integral>
    static SROOK_CXX14_CONSTEXPR Integral apply(Integral n) SROOK_NOEXCEPT_TRUE
    {
#ifdef _MSC_VER
        Integral result;
        return _BitScanReverse64(&result, n) ? result : n;
#else
        return 63 - __builtin_clzll(srook::move(n));
#endif
    }
};
#endif

template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<is_unsigned<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type msb(Integral x)
{
#ifdef SROOK_MSB_HAS_COMPILER_INTRINSIC
    return builtin_bitscan<sizeof(Integral)>::apply(srook::move(x));
#else
    return do_msb(srook::move(x));
#endif
}

} // namespace detail

template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<is_unsigned<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type msb(Integral x)
{
    return detail::msb(srook::move(x));
}

template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<is_signed<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type msb(Integral x)
{
    return detail::msb(static_cast<SROOK_DEDUCED_TYPENAME make_unsigned<Integral>::type>(x));
}

template <class FloatingPoint, SROOK_REQUIRES(is_floating_point<FloatingPoint>::value)>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(FloatingPoint)>::result_type msb(FloatingPoint x)
{
    SROOK_STATIC_ASSERT(numeric_limits<FloatingPoint>::is_iec559, "Floating point type must be iec559");
    typedef SROOK_DEDUCED_TYPENAME conditional<sizeof(FloatingPoint) == 4, srook::uint32_t, srook::uint64_t>::type integral_type;
    integral_type value{};
    srook::cstring::memcpy(&value, &x, sizeof(integral_type));
    return detail::msb(srook::move(value));
}

template <class Pointer>
inline SROOK_ASM_CONSTEXPR
SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(std::uintptr_t)>::result_type msb(Pointer* ptr)
{
    return detail::msb(reinterpret_cast<std::uintptr_t>(ptr));
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR bool msb(bool b)
{
    return b;
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR std::nullptr_t msb(std::nullptr_t x)
{
    return x;
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, bit, srook)

#undef SROOK_ASM_CONSTEXPR
#undef SROOK_MSB_HAS_COMPILER_INTRINSIC
#endif
#endif
