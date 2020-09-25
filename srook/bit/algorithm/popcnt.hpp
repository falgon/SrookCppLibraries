// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BIT_POP_COUNT_HPP
#define INCLUDED_SROOK_BIT_POP_COUNT_HPP

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

#if defined(__OPENCL_CL_H) && defined(__OPENCL_VERSION__) 
#   define SROOK_HAS_OPENCL_H 1
#endif

#include <srook/cstring/avx/algorithm/memcpy/detail/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <type_traits>
#include <srook/type_traits.hpp>

SROOK_NESTED_NAMESPACE(srook, bit, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t>
struct popcnt;

template <>
struct popcnt<1> {
    typedef srook::uint8_t result_type;
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type value)
    {
#if SROOK_HAS_OPENCL_H
        return popcount(value);
#else
        value = result_type((value & 0x55) + ((value >> 1) & 0x55));
        value = result_type((value & 0x33) + ((value >> 2) & 0x33));
        return result_type((value & 0x0f) + ((value >> 4) & 0x0f));
#endif
    }
};

template <>
struct popcnt<2> {
    typedef srook::uint16_t result_type;
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type value)
    {
#if SROOK_HAS_OPENCL_H
        return popcount(value);
#elif defined(_MSC_VER)
        return __popcnt16(value);
#else
        value = result_type((value & 0x5555) + ((value >> 1) & 0x5555));
        value = result_type((value & 0x3333) + ((value >> 2) & 0x3333));
        value = result_type((value & 0x0f0f) + ((value >> 4) & 0x0f0f));
        return result_type((value & 0x00ff) + ((value >> 8) & 0x00ff));
#endif
    }
};

template <>
struct popcnt<4> {
    typedef srook::uint32_t result_type;

    static SROOK_FORCE_INLINE SROOK_CONSTEXPR result_type apply(result_type value)
    {
#if __CUDACC__
        return __popc(value);
#elif SROOK_HAS_OPENCL_H
        return popcount(value);
#elif ((defined(_MSC_VER) && defined(_M_X64)) || defined(__POPCNT__)) && !defined(__clang__)
        return _mm_popcnt_u32(value);
#elif defined(_MSC_VER)
        return __popcnt(value);
#elif defined(__POPCNT__) && defined(__clang__) && defined(__x86_64__)
        result_type r;
        asm ("popcnt %1, %0" : "=r"(r) : "r"(value));
        return r;
#elif defined(__GNUC__) && defined(__x86_64__)
        return __builtin_popcount(value);
#else
        value = value - ((value >> 1) & 0x55555555);
        value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
        return ((value + (value >> 4) & 0x0f0f0f0f) * 0x01010101) >> 24;
#endif
    }
};

template <>
struct popcnt<8> {
    typedef srook::uint64_t result_type;
    
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint64_t apply(srook::uint64_t value)
    {
#if __CUDACC__
        return __popcll(value);
#elif SROOK_HAS_OPENCL_H
        return popcount(value);
#elif ((defined(_MSC_VER) && defined(_M_X64)) || defined(__POPCNT__)) && !defined(__clang__)
        return _mm_popcnt_u64(value);
#elif defined(_MSC_VER)
        return __popcnt64(value);
#elif defined(__POPCNT__) && defined(__clang__) && defined(__x86_64__)
        asm ("popcntq %1, %0" : "=r"(value) : "r"(value));
        return value;
#elif defined(__GNUC__) && defined(__x86_64__)
        return __builtin_popcountll(value);
#else
        value = (value & 0x5555555555555555) + ((value >> 1) & 0x5555555555555555);
        value = (value & 0x3333333333333333) + ((value >> 2) & 0x3333333333333333);
        value = (value & 0x0f0f0f0f0f0f0f0f) + ((value >> 4) & 0x0f0f0f0f0f0f0f0f);
        value = (value & 0x00ff00ff00ff00ff) + ((value >> 8) & 0x00ff00ff00ff00ff);
        value = (value & 0x0000ffff0000ffff) + ((value >> 16) & 0x0000ffff0000ffff);
        return (value & 0x00000000ffffffff) + ((value >> 32) & 0x00000000ffffffff);
#endif
    }
};

} // namespace detail

SROOK_FORCE_INLINE SROOK_CONSTEXPR bool popcnt(bool value)
{
    return value;
}

SROOK_FORCE_INLINE SROOK_CONSTEXPR std::nullptr_t popcnt(std::nullptr_t x) 
{ 
    return x;
}

template <class T, SROOK_REQUIRES(type_traits::detail::Land<std::is_unsigned<T>, is_integral<T>>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(T)>::result_type
popcnt(T value)
{
    return detail::popcnt<sizeof(T)>::apply(value);
}

template <class Pointer>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(std::uintptr_t)>::result_type
popcnt(Pointer* value)
{
    return popcnt(reinterpret_cast<std::uintptr_t>(value));
}

template <typename T, SROOK_REQUIRES(type_traits::detail::Land<std::is_signed<T>, is_integral<T>>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME detail::popcnt<sizeof(SROOK_DEDUCED_TYPENAME std::make_unsigned<T>::type)>::result_type
popcnt(T value)
{
    return popcnt(static_cast<SROOK_DEDUCED_TYPENAME std::make_unsigned<T>::type>(value));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, bit, srook)

#if defined(__clang__)
#   pragma clang  diagnostic pop
#endif
#endif
#endif
