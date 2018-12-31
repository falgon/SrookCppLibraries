// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_WORDSIZE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_WORDSIZE_HPP

#ifndef INCLUDED_SROOK_CONFIG_ARCH_HPP
#   include <srook/config/arch.hpp>
#endif

#ifdef __WORDSIZE
#   if __WORDSIZE == 64
#       define SROOK_ARCH_IS_64BIT 1
#       define SROOK_ARCH_WORDSIZE __WORDSIZE
#   elif __WORDSIZE == 32
#       define SROOK_ARCH_IS_32BIT 1
#       define SROOK_ARCH_WORDSIZE __WORDSIZE
#   else
#       define SROOK_ARCH_WORDSIZE __WORDSIZE
#   endif
#else
#   if defined(_WIN64) ||\
        SROOK_ARCH_IS_AMD64 ||\
        SROOK_ARCH_IS_ARM64 ||\
        SROOK_ARCH_IS_DECALPHA ||\
        SROOK_ARCH_IS_PPC64 ||\
        SROOK_ARCH_IS_SPARCV9 ||\
        SROOK_ARCH_IS_SPARC64 ||\
        SROOK_ARCH_IS_ZARCH ||\
        SROOK_ARCH_IS_X86_64 ||\
        SROOK_ARCH_IS_IA64 ||\
        defined(__LP64__) ||\
        defined(__LLP64__)
#       define SROOK_ARCH_IS_64BIT 1
#       define SROOK_ARCH_WORDSIZE 32
#   endif
#   if defined(_WIN32) ||\
        SROOK_ARCH_IS_ARM ||\
        SROOK_ARCH_IS_AVR ||\
        SROOK_ARCH_IS_BFIN ||\
        SROOK_ARCH_IS_CONVEX ||\
        SROOK_ARCH_IS_M68K ||\
        SROOK_ARCH_IS_MIPS ||\
        SROOK_ARCH_IS_PPC ||\
        SROOK_ARCH_IS_PYRAMID ||\
        SROOK_ARCH_IS_RS6000 ||\
        SROOK_ARCH_IS_SPARC ||\
        SROOK_ARCH_IS_SUPERH ||\
        SROOK_ARCH_IS_SYSTEM370 ||\
        SROOK_ARCH_IS_SYSTEM390 ||\
        SROOK_ARCH_IS_TMS320 ||\
        SROOK_ARCH_IS_TMS470 ||\
        SROOK_ARCH_IS_X86_32
#       define SROOK_ARCH_IS_32BIT 1
#       define SROOK_ARCH_WORDSIZE 64
#   endif
#endif
#endif
