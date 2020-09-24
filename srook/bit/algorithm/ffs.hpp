// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BIT_FFS_HPP
#define INCLUDED_SROOK_BIT_FFS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config/compiler/msvc/includes/intrin.h>
#include <srook/bit/algorithm/msb.hpp>
#include <srook/cstring/memcpy.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/limits/numeric_limits.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#if ((defined(_MSC_VER) && SROOK_ARCH_IS_X86_64) || defined(__GNUC__))
#   define SROOK_ASM_CONSTEXPR SROOK_CONSTEXPR
#else
#   define SROOK_ASM_CONSTEXPR
#endif
#if defined(__GNUC__)
#   define SROOK_MSB_HAS_COMPILER_INTRINSIC 1
#endif

SROOK_NESTED_NAMESPACE(srook, bit, algorithm) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class Integral>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type 
do_ffs(Integral x)
{
    SROOK_STATIC_ASSERT(sizeof(Integral) % 2 == 0, "The Integral type must be an even bit size.");
    SROOK_STATIC_ASSERT(CHAR_BIT == 8, "CHAR_BIT must be 8");
    return srook::bit::algorithm::msb(x) + 1;
}

#ifdef SROOK_MSB_HAS_COMPILER_INTRINSIC
template <std::size_t>
struct builtin_ffs {
    template <class Integral>
    static SROOK_CONSTEXPR Integral apply(Integral n) SROOK_NOEXCEPT_TRUE
    {
        return do_ffs(srook::move(n));
    }
};

template <>
struct builtin_ffs<4> {
    template <class Integral>
    static SROOK_CXX14_CONSTEXPR Integral apply(Integral n) SROOK_NOEXCEPT_TRUE
    {
        return __builtin_ffs(srook::move(n));
    }
};

template <>
struct builtin_ffs<8> {
    template <class Integral>
    static SROOK_CXX14_CONSTEXPR Integral apply(Integral n) SROOK_NOEXCEPT_TRUE
    {
        return __builtin_ffsll(srook::move(n));
    }
};
#endif

template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<is_unsigned<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type ffs(Integral x)
{
    return x ?
#ifdef SROOK_MSB_HAS_COMPILER_INTRINSIC
        builtin_ffs<sizeof(Integral)>::apply(srook::move(x)) :
#else
        do_ffs(srook::move(x)) :
#endif
    x;
}

} // namespace detail

template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<is_unsigned<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type ffs(Integral x)
{
    return detail::ffs(srook::move(x));
}

template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<is_signed<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type ffs(Integral x)
{
    return detail::ffs(static_cast<SROOK_DEDUCED_TYPENAME make_unsigned<Integral>::type>(x));
}

template <class FloatingPoint, SROOK_REQUIRES(is_floating_point<FloatingPoint>::value)>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(FloatingPoint)>::result_type ffs(FloatingPoint x)
{
    SROOK_STATIC_ASSERT(numeric_limits<FloatingPoint>::is_iec559, "Floating point type must be iec559");
    typedef SROOK_DEDUCED_TYPENAME conditional<sizeof(FloatingPoint) == 4, srook::uint32_t, srook::uint64_t>::type integral_type;
    integral_type value{};
    srook::cstring::memcpy(&value, &x, sizeof(integral_type));
    return detail::ffs(srook::move(value));
}

template <class Pointer>
inline SROOK_ASM_CONSTEXPR
SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(std::uintptr_t)>::result_type ffs(Pointer* ptr)
{
    return detail::ffs(reinterpret_cast<std::uintptr_t>(ptr));
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR bool ffs(bool b)
{
    return b;
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR std::nullptr_t ffs(std::nullptr_t x)
{
    return x;
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, bit, srook)

#undef SROOK_ASM_CONSTEXPR
#undef SROOK_MSB_HAS_COMPILER_INTRINSIC
#endif
#endif
