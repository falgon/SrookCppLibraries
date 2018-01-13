// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BIT_ALGORITHM_REVERSE_HPP
#define INCLUDED_SROOK_BIT_ALGORITHM_REVERSE_HPP

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
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <type_traits>
#include <srook/type_traits.hpp>
#include <srook/cstdint.hpp>

SROOK_NESTED_NAMESPACE(srook, bit, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t>
struct reverse;

template <>
struct reverse<1> {
    typedef srook::uint8_t result_type;
public:
#if !SROOK_ARCH_IS_X86_64
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type value)
    {
        return result_type(((value * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32);
    }
#else
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type value)
    {
        return result_type(((value * 0x0802LU & 0x22110LU) | (value * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16); 
    }
#endif
};

template <>
struct reverse<2> {
    typedef srook::uint16_t result_type;
public:
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type value)
    {
        value = result_type(((value >> 1) & 0x5555) | ((value & 0x5555) << 1));
        value = result_type(((value >> 2) & 0x3333) | ((value & 0x3333) << 2));
        value = result_type(((value >> 4) & 0x0f0f) | ((value & 0x0f0f) << 4));
        return result_type((value >> 8) | (value << 8));
    }
};

template <>
struct reverse<4> {
    typedef srook::uint32_t result_type;
public:
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type value)
    {
        value = ((value >> 1) & 0x55555555) | ((value & 0x55555555) << 1);
        value = ((value >> 2) & 0x33333333) | ((value & 0x33333333) << 2);
        value = ((value >> 4) & 0x0f0f0f0f) | ((value & 0x0f0f0f0f) << 4);
        value = ((value >> 8) & 0x00ff00ff) | ((value & 0x00ff00ff) << 8);
        return (value >> 16) | (value << 16);
    }
};

template <>
struct reverse<8> {
    typedef srook::uint64_t result_type;
public:
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type value)
    {
        value = ((value >> 1) & 0x5555555555555555) | ((value & 0x5555555555555555) << 1);
        value = ((value >> 2) & 0x3333333333333333) | ((value & 0x3333333333333333) << 2);
        value = ((value >> 4) & 0x0f0f0f0f0f0f0f0f) | ((value & 0x0f0f0f0f0f0f0f0f) << 4);
        value = ((value >> 8) & 0x00ff00ff00ff00ff) | ((value & 0x00ff00ff00ff00ff) << 8);
        value = ((value >> 16) & 0x0000ffff0000ffff) | ((value & 0x0000ffff0000ffff) << 16);
        return (value >> 32) | (value << 32);
    }
};
        
} // namespace detail

template <typename Integral, SROOK_REQUIRES(type_traits::detail::Land<std::is_unsigned<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::reverse<sizeof(Integral)>::result_type
reverse(Integral x)
{
    return detail::reverse<sizeof(Integral)>::apply(x);
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR bool reverse(bool x)
{
    return !x;
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR std::nullptr_t reverse(std::nullptr_t x)
{
    return x;
}

template <typename Pointer>
SROOK_FORCE_INLINE SROOK_CONSTEXPR std::uintptr_t reverse(Pointer* p)
{
    return reverse(reinterpret_cast<std::uintptr_t>(p));
}

template <typename T, SROOK_REQUIRES(std::is_enum<T>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME std::underlying_type<T>::type reverse(T x)
{
    return reverse(static_cast<SROOK_DEDUCED_TYPENAME std::underlying_type<T>::type>(x));
}

template <typename Integral, SROOK_REQUIRES(type_traits::detail::Land<std::is_signed<Integral>, is_integral<Integral>>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME detail::reverse<sizeof(SROOK_DEDUCED_TYPENAME std::make_unsigned<Integral>::type)>::result_type
reverse(Integral value)
{
    return reverse(static_cast<SROOK_DEDUCED_TYPENAME std::make_unsigned<Integral>::type>(value));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, bit, srook)

#if defined(__clang__)
#   pragma clang  diagnostic pop
#endif

#endif
#endif
