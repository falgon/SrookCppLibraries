// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CHRONO_RDTSC_HPP
#define INCLUDED_SROOK_CHRONO_RDTSC_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#   if _MSC_VER >= 1100
#       include <intrin.h>
#       pragma intrinsic(__rdtsc)
#       define SROOK_HAS_MSC_INTRINSICS_RDTSC 1
#   endif
#   if _MSC_FULL_VER >= 150021022
#       define SROOK_HAS_MSC_INTRINSICS_RDTSCP 1
#       pragma intrinsic(__rdtscp)
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cstdint.hpp>

SROOK_NESTED_NAMESPACE(srook, chrono, intrinsic) {
SROOK_INLINE_NAMESPACE(v1)

SROOK_FORCE_INLINE srook::uint64_t rdtsc()
{
#ifdef SROOK_HAS_MSC_INTRINSICS_RDTSC
    return __rdtsc();
#elif (defined(__aarch64__) || defined(__x86_64__)) && defined(__GNUC__)
    srook::uint32_t low, high;
    __asm__ __volatile__ ("rdtsc" : "=a"(low), "=d"(high));
    return (static_cast<srook::uint64_t>(high) << 32) | low;
#elif defined(__i386__) && defined(__GNUC__)
    srook::uint64_t ret;
    __asm__ __volatile__ (".byte 0x0f, 0x31" : "=A" (ret));
    return ret;
#elif defined(__powerpc__) && defined(__GNUC__)
    srook::uint32_t low, high, t;
    __asm__ __volatile__ (
        "0:             \n"
        "\tmftbu   %0   \n"
        "\tmftb    %1   \n"
        "\tmftbu   %2   \n"
        "\tcmpw    %2,%0\n"
        "\tbne     0b   \n"
        : "=r"(high),"=r"(low),"=r"(t));
    return (static_cast<srook::uint64_t>(high) << 32) | low;
#else
#   error This environment is not supported
#endif
}

SROOK_FORCE_INLINE srook::uint64_t rdtscp()
{
#ifdef SROOK_HAS_MSC_INTRINSICS_RDTSCP
    return __rdtscp();
#elif (defined(__aarch64__) || defined(__x86_64__)) && defined(__GNUC__)
    srook::uint32_t low, high;
    __asm__ __volatile__ ("rdtscp" : "=a"(low), "=d"(high));
    return (static_cast<srook::uint64_t>(high) << 32) | low;
#else
#   error This environment is not supported
#endif
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(intrinsi, chrono, srook)
#endif
