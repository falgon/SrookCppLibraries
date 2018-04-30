// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BIT_ALGORITHM_NEXT_PERMUTATION_HPP
#define INCLUDED_SROOK_BIT_ALGORITHM_NEXT_PERMUTATION_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#ifdef __GNUC__
#   pragma GCC system_header
#elif defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang ignored "-Wvariadic-macros"
#endif

#include <srook/config.hpp>
#include <srook/config/compiler/msvc/includes/intrin.h>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/cstdint.hpp>
#include <srook/bit/algorithm/ntz.hpp>
#include <type_traits>
#include <srook/type_traits.hpp>

SROOK_NESTED_NAMESPACE(srook, bit, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

SROOK_FORCE_INLINE SROOK_CONSTEXPR bool next_permutation(bool value)
{
    return !value;
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR std::nullptr_t next_permutation(std::nullptr_t x)
{
    return x;
}

template <typename Integral, SROOK_REQUIRES(type_traits::detail::Land<is_integral<Integral>, std::is_unsigned<Integral>>::value)>
SROOK_FORCE_INLINE 
#if ((defined(_MSC_VER) && SROOK_ARCH_IS_X86_64) || defined(__GNUC__))
SROOK_CONSTEXPR 
#endif
Integral next_permutation(Integral value) SROOK_NOEXCEPT_TRUE
{
    const Integral t = value | (value - 1);
    return (t + 1) | (((~t & -~t) - 1) >> (ntz(value) + 1));
}

template <typename Integral, SROOK_REQUIRES(type_traits::detail::Land<is_integral<Integral>, std::is_signed<Integral>>::value)>
SROOK_FORCE_INLINE 
#if ((defined(_MSC_VER) && SROOK_ARCH_IS_X86_64) || defined(__GNUC__))
SROOK_CONSTEXPR 
#endif
SROOK_DEDUCED_TYPENAME std::make_unsigned<Integral>::type next_permutation(Integral value)
{
    return next_permutation(static_cast<SROOK_DEDUCED_TYPENAME std::make_unsigned<Integral>>(value));
}

template <typename Pointer>
SROOK_FORCE_INLINE
#if ((defined(_MSC_VER) && SROOK_ARCH_IS_X86_64) || defined(__GNUC__))
SROOK_CONSTEXPR
#endif
SROOK_DEDUCED_TYPENAME std::uintptr_t next_permutation(Pointer* p)
{
    return next_permutation(reinterpret_cast<std::uintptr_t>(p));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, bit, srook)

#if defined(__clang__)
#   pragma clang  diagnostic pop
#endif
#endif
#endif
