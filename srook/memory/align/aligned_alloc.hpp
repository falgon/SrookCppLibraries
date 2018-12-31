// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALIGNED_ALLOC_HPP
#define INCLUDED_SROOK_MEMORY_ALIGNED_ALLOC_HPP

#if defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#   include <unistd.h>
#endif

#if defined(__APPLE__) || defined(__APPLE_CC__) || defined(macintosh)
#   include <AvailabilityMacros.h>
#endif

#ifndef SROOK_CONFIG_ALIGN_USE_ALLOCATE
#   if /* SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT || */ defined(_ISOC11_SOURCE) // `std::aligned_alloc` is not yet implemented in C++17 mode for both GCC 7.3.1 and Clang 6.0.0
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_STD 1
#   elif (defined(_MSC_VER) && !(defined(UNDER_CE))) || defined(__MINGW32__) && (__MSVCRT_VERSION__ >= 0x0700)
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_MSVC 1
#   elif MAC_OS_X_VERSION_MIN_REQUIRED >= 1090
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_POSIX 1
#   elif MAC_OS_X_VERSION_MIN_REQUIRED >= 1060
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_MACOS 1
#   elif defined(__ANDROID__)
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_ANDROID 1
#   elif defined(__SunOS_5_11) || defined(__SunOS_5_12)
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_POSIX 1
#   elif defined(sun) || defined(__sun)
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_SUNOS 1
#   elif (_POSIX_C_SOURCE >= 200112L) || (_XOPEN_SOURCE >= 600)
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_POSIX 1
#   elif defined(__INTEL_COMPILER)
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_MM 1
#   elif defined(__GNUC__) && defined(__linux__)
#       define SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_GNU_MM 1
#   endif
#endif
#include <srook/memory/align/detail/aligned_alloc.hpp>

#endif
