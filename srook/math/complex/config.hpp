// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_COMPLEX_CONFIG_HPP
#define INCLUDED_SROOK_MATH_COMPLEX_CONFIG_HPP

#ifndef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#ifdef __cplusplus
#   include <ccomplex>
#else
#   include <complex.h>
#   undef complex // for std::complex
#endif

#define SROOK_COMPLEX _Complex
#define SROOK_COMPLEX_REAL __real__
#define SROOK_COMPLEX_IMAG __imag__

#ifdef __STD_IEC_559_COMPLEX__ 
#   define SROOK_IMAGINARY _Imaginary
#endif

#include <srook/config.hpp>
#ifdef SROOK_GCC
SROOK_NESTED_NAMESPACE(srook, math) {
#   if SROOK_ARCH_IS_IA64 || SROOK_ARCH_IS_X86_64 || defined(__i386__) || defined(__hpux) 
    
__extension__ typedef SROOK_COMPLEX float __attribute__((mode(TC))) _Complex128;
__extension__ typedef SROOK_COMPLEX float __attribute__((mode(XC))) _Complex80;

#   endif
#   if defined(__VSX__) && SROOK_ARCH_IS_PPC &&\
    (defined(__linux) || defined(__linux__) || defined(__gnu_linux__) || defined(linux))

__extension__ typedef _Complex float __attribute__((mode(KC))) _Complex_float128;
__extension__ typedef _Complex float __attribute__((mode(IC))) _Complex_ibm128;

#   endif
} SROOK_NESTED_NAMESPACE_END(srook, math)
#endif

#endif
