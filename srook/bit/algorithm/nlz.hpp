// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BIT_ALGORITHM_NUMBER_OF_LEADING_ZERO_HPP
#define INCLUDED_SROOK_BIT_ALGORITHM_NUMBER_OF_LEADING_ZERO_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/bit/algorithm/popcnt.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#if ((defined(_MSC_VER) && SROOK_ARCH_IS_X86_64) || defined(__GNUC__))
#   define SROOK_ASM_CONSTEXPR SROOK_CONSTEXPR
#else
#   define SROOK_ASM_CONSTEXPR
#endif

SROOK_NESTED_NAMESPACE(srook, bit, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class Integral>
SROOK_CONSTEXPR Integral shift_or(Integral x, Integral max_bits, Integral bits = 1)
{
    return bits == max_bits ? static_cast<Integral>(~(x | (x >> max_bits))) : shift_or(static_cast<Integral>(x | (x >> bits)), max_bits, static_cast<Integral>(bits << 1));
}

} // namespace detail

template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<is_unsigned<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type nlz(Integral x)
{
    return static_cast<Integral>(popcnt(detail::shift_or(x, static_cast<Integral>((sizeof(x) * CHAR_BIT) >> 1))));
}

template <class Integral, SROOK_REQUIRES(type_traits::detail::Land<is_signed<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_ASM_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(Integral)>::result_type nlz(Integral x)
{
    return nlz(static_cast<SROOK_DEDUCED_TYPENAME make_unsigned<Integral>::type>(x));
}

template <class Pointer>
inline SROOK_ASM_CONSTEXPR
SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(std::uintptr_t)>::result_type nlz(Pointer* ptr)
{
    return nlz(reinterpret_cast<std::uintptr_t>(ptr));
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR bool nlz(bool b)
{
    return !b;
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR std::nullptr_t nlz(std::nullptr_t x)
{
    return x;
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, bit, srook)

#undef SROOK_ASM_CONSTEXPR
#endif
#endif
