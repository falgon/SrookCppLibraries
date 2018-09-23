// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTDFLOAT_TYPE_HPP
#define INCLUDED_SROOK_CSTDFLOAT_TYPE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#ifdef __GNUC__
#   define __STDC_WANT_IEC_60559_TYPES_EXT__
#endif
#ifdef __cplusplus
#   include <cfloat>
#else
#   include <float.h>
#endif

#include <srook/config/cpp_predefined/feature_testing.hpp>
#ifndef SROOK_HAS_INCLUDE_BOOST_CSTDFLOAT_TYPES
#   ifndef _BOOST_CSTDFLOAT_TYPES_2014_01_09_HPP_
#       if SROOK_HAS_INCLUDE(<boost/math/cstdfloat/cstdfloat_types.hpp>)
#           include <boost/math/cstdfloat/cstdfloat_types.hpp>
#           define SROOK_HAS_INCLUDE_BOOST_CSTDFLOAT_TYPES 1
#       endif
#   else
#       define SROOK_HAS_INCLUDE_BOOST_CSTDFLOAT_TYPES 1
#   endif
#endif

#ifndef SROOK_HAS_INCLUDE_BOOST_CSTDFLOAT_TYPES
#   if (!defined(FLT_RADIX) || ((defined(FLT_RADIX) && (FLT_RADIX != 2))))
#       error The compiler does not support any radix-2 floating-point types required for <srook/cstdfloat.hpp>.
#   endif
#endif

#define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH  0
#define SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  0
#define SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  0
#define SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  0
#define SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  0
#define SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE 0
   
#if defined(FLT_MANT_DIG) && defined(FLT_MAX_EXP)
#   if ((FLT_MANT_DIG == 11) && (FLT_MAX_EXP == 16) && (SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 0))
#       define SROOK_CSTDFLOAT_FLOAT16_NATIVE_TYPE float
#       undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#       define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 16
#       undef  SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE
#       define SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  1
#       define SROOK_FLOAT16_C(x)  (x ## F)
#       define SROOK_CSTDFLOAT_FLOAT_16_MIN  FLT_MIN
#       define SROOK_CSTDFLOAT_FLOAT_16_MAX  FLT_MAX
#   elif ((FLT_MANT_DIG == 24) && (FLT_MAX_EXP == 128) && (SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
#       define SROOK_CSTDFLOAT_FLOAT32_NATIVE_TYPE float
#       undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#       define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
#       undef  SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE
#       define SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
#       define SROOK_FLOAT32_C(x)  (x ## F)
#       define SROOK_CSTDFLOAT_FLOAT_32_MIN  FLT_MIN
#       define SROOK_CSTDFLOAT_FLOAT_32_MAX  FLT_MAX
#   elif ((FLT_MANT_DIG == 53) && (FLT_MAX_EXP == 1024) && (SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
#       define SROOK_CSTDFLOAT_FLOAT64_NATIVE_TYPE float
#       undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#       define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
#       undef  SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE
#       define SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
#       define SROOK_FLOAT64_C(x)  (x ## F)
#       define SROOK_CSTDFLOAT_FLOAT_64_MIN  FLT_MIN
#       define SROOK_CSTDFLOAT_FLOAT_64_MAX  FLT_MAX
#   elif ((FLT_MANT_DIG == 64) && (FLT_MAX_EXP == 16384) && (SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
#       define SROOK_CSTDFLOAT_FLOAT80_NATIVE_TYPE float
#       undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#       define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
#       undef  SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
#       define SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
#       define SROOK_FLOAT80_C(x)  (x ## F)
#       define SROOK_CSTDFLOAT_FLOAT_80_MIN  FLT_MIN
#       define SROOK_CSTDFLOAT_FLOAT_80_MAX  FLT_MAX
#   elif ((FLT_MANT_DIG == 113) && (FLT_MAX_EXP == 16384) && (SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
#       define SROOK_CSTDFLOAT_FLOAT128_NATIVE_TYPE float
#       undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#       define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
#       undef  SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
#       define SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
#       define SROOK_FLOAT128_C(x)  (x ## F)
#       define SROOK_CSTDFLOAT_FLOAT_128_MIN  FLT_MIN
#       define SROOK_CSTDFLOAT_FLOAT_128_MAX  FLT_MAX
#   endif
#   if defined(DBL_MANT_DIG) && defined(DBL_MAX_EXP)
#       if ((DBL_MANT_DIG == 11) && (DBL_MAX_EXP == 16) && (SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 0))
#           define SROOK_CSTDFLOAT_FLOAT16_NATIVE_TYPE double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 16
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  1
#           define SROOK_FLOAT16_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_16_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_16_MAX  DBL_MAX
#       elif ((DBL_MANT_DIG == 24) && (DBL_MAX_EXP == 128) && (SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
#           define SROOK_CSTDFLOAT_FLOAT32_NATIVE_TYPE double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
#           define SROOK_FLOAT32_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_32_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_32_MAX  DBL_MAX
#       elif ((DBL_MANT_DIG == 53) && (DBL_MAX_EXP == 1024) && (SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
#           define SROOK_CSTDFLOAT_FLOAT64_NATIVE_TYPE double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
#           define SROOK_FLOAT64_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_64_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_64_MAX  DBL_MAX
#       elif ((DBL_MANT_DIG == 64) && (DBL_MAX_EXP == 16384) && (SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
#           define SROOK_CSTDFLOAT_FLOAT80_NATIVE_TYPE double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
#           define SROOK_FLOAT80_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_80_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_80_MAX  DBL_MAX
#       elif ((DBL_MANT_DIG == 113) && (DBL_MAX_EXP == 16384) && (SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
#           define SROOK_CSTDFLOAT_FLOAT128_NATIVE_TYPE double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
#           define SROOK_FLOAT128_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_128_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_128_MAX  DBL_MAX
#       endif
#   endif
#   if (defined(LDBL_MANT_DIG) && defined(LDBL_MAX_EXP))
#      if ((LDBL_MANT_DIG == 11) && (LDBL_MAX_EXP == 16) && (SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 0)) 
#           define SROOK_CSTDFLOAT_FLOAT16_NATIVE_TYPE long double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 16
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  1
#           define SROOK_FLOAT16_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_16_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_16_MAX  DBL_MAX
#       elif ((LDBL_MANT_DIG == 24) && (LDBL_MAX_EXP == 128) && (SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
#           define SROOK_CSTDFLOAT_FLOAT32_NATIVE_TYPE long double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
#           define SROOK_FLOAT32_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_32_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_32_MAX  DBL_MAX
#       elif ((LDBL_MANT_DIG == 53) && (LDBL_MAX_EXP == 1024) && (SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))           
#           define SROOK_CSTDFLOAT_FLOAT64_NATIVE_TYPE long double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
#           define SROOK_FLOAT64_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_64_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_64_MAX  DBL_MAX
#       elif ((LDBL_MANT_DIG == 64) && (LDBL_MAX_EXP == 16384) && (SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))           
#           define SROOK_CSTDFLOAT_FLOAT80_NATIVE_TYPE long double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
#           define SROOK_FLOAT80_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_80_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_80_MAX  DBL_MAX
#       elif((LDBL_MANT_DIG == 113) && (LDBL_MAX_EXP == 16384) && (SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
#           define SROOK_CSTDFLOAT_FLOAT128_NATIVE_TYPE long double
#           undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#           define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
#           undef  SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
#           define SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
#           define SROOK_FLOAT128_C(x)  (x)
#           define SROOK_CSTDFLOAT_FLOAT_128_MIN  DBL_MIN
#           define SROOK_CSTDFLOAT_FLOAT_128_MAX  DBL_MAX
#       endif
#   endif
#endif

#include <srook/config.hpp>
#include <srook/limits/numeric_limits.hpp>
#if defined(SROOK_HAS_FLOAT128) && (SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0)
#   ifdef SROOK_GCC
#       if SROOK_GCC_VERSION < 40900
extern "C" {
#           include <quadmath.h>
}
#       else
#           include <quadmath.h>
#       endif
#   endif
SROOK_NESTED_NAMESPACE(srook, intrinsic_types) { SROOK_INLINE_NAMESPACE

#   ifdef SROOK_GCC
__extension__ typedef __float128 float128_t;
#   elif defined(__INTEL_COMPILER)
typedef _Quad float128_t;
#   endif

SROOK_INLINE_NAMESPACE_END } SROOK_NESTED_NAMESPACE_END(intrinsic_type, srook)

#   ifndef SROOK_HAS_INCLUDE_BOOST_CSTDFLOAT_TYPES
#       define SROOK_CSTDFLOAT_FLOAT128_NATIVE_TYPE boost::math::cstdfloat::detail::float_internal128_t
#       undef  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#       define SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
#       undef  SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
#       define SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
#       define SROOK_FLOAT128_C(x)  (x ## Q)
#       define SROOK_CSTDFLOAT_FLOAT128_MIN  3.36210314311209350626267781732175260e-4932Q
#       define SROOK_CSTDFLOAT_FLOAT128_MAX  1.18973149535723176508575932662800702e+4932Q
#       define SROOK_CSTDFLOAT_FLOAT128_EPS  1.92592994438723585305597794258492732e-0034Q
#   endif
#endif

#ifndef SROOK_HAS_INCLUDE_BOOST_CSTDFLOAT_TYPES
#   if ((SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  == 0)  \
        && (SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  == 0)  \
        && (SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  == 0)  \
        && (SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  == 0)  \
        && (SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
#       error The compiler does not support any of the floating-point types required for <srook/cstdfloat.hpp>.
#   endif
#   if (SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 1)
#       define SROOK_FLOAT_FAST16_MIN   SROOK_CSTDFLOAT_FLOAT_16_MIN
#       define SROOK_FLOAT_LEAST16_MIN  SROOK_CSTDFLOAT_FLOAT_16_MIN
#       define SROOK_FLOAT_FAST16_MAX   SROOK_CSTDFLOAT_FLOAT_16_MAX
#       define SROOK_FLOAT_LEAST16_MAX  SROOK_CSTDFLOAT_FLOAT_16_MAX
#   endif
#   if (SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 1)
#       define SROOK_FLOAT_FAST32_MIN   SROOK_CSTDFLOAT_FLOAT_32_MIN
#       define SROOK_FLOAT_LEAST32_MIN  SROOK_CSTDFLOAT_FLOAT_32_MIN
#       define SROOK_FLOAT_FAST32_MAX   SROOK_CSTDFLOAT_FLOAT_32_MAX
#       define SROOK_FLOAT_LEAST32_MAX  SROOK_CSTDFLOAT_FLOAT_32_MAX
#   endif
#   if (SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 1)
#       define SROOK_FLOAT_FAST64_MIN   SROOK_CSTDFLOAT_FLOAT_64_MIN
#       define SROOK_FLOAT_LEAST64_MIN  SROOK_CSTDFLOAT_FLOAT_64_MIN
#       define SROOK_FLOAT_FAST64_MAX   SROOK_CSTDFLOAT_FLOAT_64_MAX
#       define SROOK_FLOAT_LEAST64_MAX  SROOK_CSTDFLOAT_FLOAT_64_MAX
#   endif
#   if (SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 1)
#       define SROOK_FLOAT_FAST80_MIN   SROOK_CSTDFLOAT_FLOAT_80_MIN
#       define SROOK_FLOAT_LEAST80_MIN  SROOK_CSTDFLOAT_FLOAT_80_MIN
#       define SROOK_FLOAT_FAST80_MAX   SROOK_CSTDFLOAT_FLOAT_80_MAX
#       define SROOK_FLOAT_LEAST80_MAX  SROOK_CSTDFLOAT_FLOAT_80_MAX
#   endif
#   if (SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 1)
#       define SROOK_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T
#       define SROOK_FLOAT_FAST128_MIN   SROOK_CSTDFLOAT_FLOAT_128_MIN
#       define SROOK_FLOAT_LEAST128_MIN  SROOK_CSTDFLOAT_FLOAT_128_MIN
#       define SROOK_FLOAT_FAST128_MAX   SROOK_CSTDFLOAT_FLOAT_128_MAX
#       define SROOK_FLOAT_LEAST128_MAX  SROOK_CSTDFLOAT_FLOAT_128_MAX
#   endif
#   if (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 16)    
#       define SROOK_FLOATMAX_C(x) SROOK_FLOAT16_C(x)
#       define SROOK_FLOATMAX_MIN  SROOK_CSTDFLOAT_FLOAT_16_MIN
#       define SROOK_FLOATMAX_MAX  SROOK_CSTDFLOAT_FLOAT_16_MAX
#   elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 32)
#       define SROOK_FLOATMAX_C(x) SROOK_FLOAT32_C(x)
#       define SROOK_FLOATMAX_MIN  SROOK_CSTDFLOAT_FLOAT_32_MIN
#       define SROOK_FLOATMAX_MAX  SROOK_CSTDFLOAT_FLOAT_32_MAX
#   elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 64)
#       define SROOK_FLOATMAX_C(x) SROOK_FLOAT64_C(x)
#       define SROOK_FLOATMAX_MIN  SROOK_CSTDFLOAT_FLOAT_64_MIN
#       define SROOK_FLOATMAX_MAX  SROOK_CSTDFLOAT_FLOAT_64_MAX
#   elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 80)
#       define SROOK_FLOATMAX_C(x) SROOK_FLOAT80_C(x)
#       define SROOK_FLOATMAX_MIN  SROOK_CSTDFLOAT_FLOAT_80_MIN
#       define SROOK_FLOATMAX_MAX  SROOK_CSTDFLOAT_FLOAT_80_MAX
#   elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 128)
#       define SROOK_FLOATMAX_C(x) SROOK_FLOAT128_C(x)
#       define SROOK_FLOATMAX_MIN  SROOK_CSTDFLOAT_FLOAT_128_MIN
#       define SROOK_FLOATMAX_MAX  SROOK_CSTDFLOAT_FLOAT_128_MAX
#   else
#       error The maximum available floating-point width for <srook/cstdfloat.hpp> is undefined.
#   endif
#else
#   define SROOK_FLOAT_FAST16_MIN   BOOST_FLOAT_FAST16_MIN 
#   define SROOK_FLOAT_LEAST16_MIN  BOOST_FLOAT_LEAST16_MIN  
#   define SROOK_FLOAT_FAST16_MAX   BOOST_FLOAT_FAST16_MAX   
#   define SROOK_FLOAT_LEAST16_MAX  BOOST_FLOAT_LEAST16_MAX  
#   define SROOK_FLOAT_FAST32_MIN   BOOST_FLOAT_FAST32_MIN  
#   define SROOK_FLOAT_LEAST32_MIN  BOOST_FLOAT_LEAST32_MIN  
#   define SROOK_FLOAT_FAST32_MAX   BOOST_FLOAT_FAST32_MAX 
#   define SROOK_FLOAT_LEAST32_MAX  BOOST_FLOAT_LEAST32_MAX  
#   define SROOK_FLOAT_FAST64_MIN   BOOST_FLOAT_FAST64_MIN  
#   define SROOK_FLOAT_LEAST64_MIN  BOOST_FLOAT_LEAST64_MIN
#   define SROOK_FLOAT_FAST64_MAX   BOOST_FLOAT_FAST64_MAX  
#   define SROOK_FLOAT_LEAST64_MAX  BOOST_FLOAT_LEAST64_MAX  
#   define SROOK_FLOAT_FAST80_MIN   BOOST_FLOAT_FAST80_MIN
#   define SROOK_FLOAT_LEAST80_MIN  BOOST_FLOAT_LEAST80_MIN 
#   define SROOK_FLOAT_FAST80_MAXB  BOOST_FLOAT_FAST80_MAX
#   define SROOK_FLOAT_LEAST80_MAX  BOOST_FLOAT_LEAST80_MAX
#   define SROOK_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T  BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T
#   define SROOK_FLOAT_FAST128_MIN  BOOST_FLOAT_FAST128_MIN   
#   define SROOK_FLOAT_LEAST128_MIN BOOST_FLOAT_LEAST128_MIN  
#   define SROOK_FLOAT_FAST128_MAX  BOOST_FLOAT_FAST128_MAX   
#   define SROOK_FLOAT_LEAST128_MAX BOOST_FLOAT_LEAST128_MAX  
#   if (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 16)    
#       define SROOK_FLOATMAX_C(x) BOOST_FLOAT16_C(x)
#       define SROOK_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_16_MIN
#       define SROOK_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_16_MAX
#   elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 32)
#       define SROOK_FLOATMAX_C(x) BOOST_FLOAT32_C(x)
#       define SROOK_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_32_MIN
#       define SROOK_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_32_MAX
#   elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 64)
#       define SROOK_FLOATMAX_C(x) BOOST_FLOAT64_C(x)
#       define SROOK_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_64_MIN
#       define SROOK_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_64_MAX
#   elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 80)
#       define SROOK_FLOATMAX_C(x) BOOST_FLOAT80_C(x)
#       define SROOK_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_80_MIN
#       define SROOK_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_80_MAX
#   elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 128)
#       define SROOK_FLOATMAX_C(x) BOOST_FLOAT128_C(x)
#       define SROOK_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_128_MIN
#       define SROOK_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_128_MAX
#   else
#       error The maximum available floating-point width for <srook/cstdfloat.hpp> is undefined.
#   endif
#endif

namespace srook {

#if (SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 1)
    typedef SROOK_CSTDFLOAT_FLOAT16_NATIVE_TYPE float16_t;
    typedef srook::float16_t float_fast16_t;
    typedef srook::float16_t float_least16_t;

    SROOK_STATIC_ASSERT(numeric_limits<srook::float16_t>::is_iec559 == true, "srook::float16_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float16_t>::radix == 2, "srook::float16_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float16_t>::digits ==  11, "srook::float16_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float16_t>::max_exponent == 16, "srook::float16_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
#   undef SROOK_CSTDFLOAT_FLOAT_16_MIN
#   undef SROOK_CSTDFLOAT_FLOAT_16_MAX
#endif

#if (SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 1)
    typedef SROOK_CSTDFLOAT_FLOAT32_NATIVE_TYPE float32_t;
    typedef srook::float32_t float_fast32_t;
    typedef srook::float32_t float_least32_t;

    SROOK_STATIC_ASSERT(numeric_limits<srook::float32_t>::is_iec559 == true, "srook::float32_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float32_t>::radix == 2, "srook::float32_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float32_t>::digits == 24, "srook::float32_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float32_t>::max_exponent ==  128, "srook::float32_t has been detected in <srookcstdfloat>, but verification with numeric_limits fails");
#   undef SROOK_CSTDFLOAT_FLOAT_32_MIN
#   undef SROOK_CSTDFLOAT_FLOAT_32_MAX
#endif

#if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && defined(__SUNPRO_CC)
#   undef   SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
#   define  SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE 0
#   undef   SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
#   define  SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE 0
#   undef   SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#   define  SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
#endif

#if (SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 1)
    typedef SROOK_CSTDFLOAT_FLOAT64_NATIVE_TYPE float64_t;
    typedef srook::float64_t float_fast64_t;
    typedef srook::float64_t float_least64_t;

    SROOK_STATIC_ASSERT(numeric_limits<srook::float64_t>::is_iec559 == true, "srook::float64_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float64_t>::radix == 2, "srook::float64_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float64_t>::digits == 53, "srook::float64_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float64_t>::max_exponent == 1024, "srook::float64_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
#   undef SROOK_CSTDFLOAT_FLOAT_64_MIN
#   undef SROOK_CSTDFLOAT_FLOAT_64_MAX
#endif

#if (SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 1)
    typedef SROOK_CSTDFLOAT_FLOAT80_NATIVE_TYPE float80_t;
    typedef srook::float80_t float_fast80_t;
    typedef srook::float80_t float_least80_t;

    SROOK_STATIC_ASSERT(numeric_limits<srook::float80_t>::is_iec559 == true, "srook::float80_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float80_t>::radix == 2, "srook::float80_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float80_t>::digits == 64, "srook::float80_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float80_t>::max_exponent == 16384, "srook::float80_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
#   undef SROOK_CSTDFLOAT_FLOAT_80_MIN
#   undef SROOK_CSTDFLOAT_FLOAT_80_MAX
#endif

#if (SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 1)
    typedef SROOK_CSTDFLOAT_FLOAT128_NATIVE_TYPE float128_t;
    typedef srook::float128_t float_fast128_t;
    typedef srook::float128_t float_least128_t;

#   if defined(BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T) && defined(BOOST_MATH_USE_FLOAT128) && !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT)

#   else
    SROOK_STATIC_ASSERT(numeric_limits<srook::float128_t>::is_iec559 == true, "srook::float128_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float128_t>::radix == 2, "srook::float128_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float128_t>::digits == 113, "srook::float128_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
    SROOK_STATIC_ASSERT(numeric_limits<srook::float128_t>::max_exponent == 16384, "srook::float128_t has been detected in <srook/cstdfloat.hpp>, but verification with numeric_limits fails");
#   endif
#endif

#if (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 16)
    typedef srook::float16_t floatmax_t;
#elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 32)
    typedef srook::float32_t floatmax_t;
#elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 64)
    typedef srook::floa64_t floatmax_t;
#elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 80)
    typedef srook::float80_t floatmax_t;
#elif (SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 128)
    typedef srook::float128_t floatmax_t;
#else
#   error  The maximum available floating-point width for <srook/cstdfloat.hpp> is undefined.
#endif

#undef SROOK_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE
#undef SROOK_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE
#undef SROOK_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE
#undef SROOK_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
#undef SROOK_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
#undef SROOK_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
    
} // namespace srook


#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <type_traits>
#include <srook/type_traits/type_constant.hpp>

namespace std {

#ifndef __clang__
template <>
struct common_type<srook::floatmax_t, srook::floatmax_t>
    : srook::type_constant<srook::floatmax_t> {};
#endif

template <class T>
struct common_type<srook::floatmax_t, T>
    : std::conditional<
        std::is_integral<T>::value, 
        srook::floatmax_t, 
        SROOK_DEDUCED_TYPENAME std::conditional<(sizeof(srook::floatmax_t) > sizeof(T)), srook::floatmax_t, T>::type
    > {};

template <class T>
struct common_type<T, srook::floatmax_t>
    : common_type<srook::floatmax_t, T> {};

#define COMMON_QUALS_DEF(QUALS)\
    template <class T> \
    struct common_type<srook::floatmax_t QUALS, T> \
        : common_type<srook::floatmax_t, T> {}; \
    template <class T> \
    struct common_type<T, srook::floatmax_t QUALS> \
        : common_type<T, srook::floatmax_t> {}

COMMON_QUALS_DEF(const);
COMMON_QUALS_DEF(const &);
COMMON_QUALS_DEF(const &&);
COMMON_QUALS_DEF(volatile);
COMMON_QUALS_DEF(volatile &);
COMMON_QUALS_DEF(volatile &&);
COMMON_QUALS_DEF(const volatile);
COMMON_QUALS_DEF(const volatile &);
COMMON_QUALS_DEF(const volatile &&);

#undef COMMON_QUALS_DEF

} // namespace std
#endif

#if SROOK_HAS_DECIMAL_FLOATS && SROOK_HAS_INCLUDE(<decimal/decimal>)
#   include <decimal/decimal>
#endif

#if SROOK_ARCH_IS_ARM && SROOK_ARM_HAS_FP16
#   if defined(SROOK_GCC) && SROOK_HAS_INCLUDE(<arm_fp16.h>)
#       include <arm_fp16.h>
#   endif
#endif

SROOK_NESTED_NAMESPACE(srook, intrinsic_types) {

#if defined(SROOK_HAS_DECIMAL_FLOATS) && defined(SROOK_GCC)
__extension__ typedef _Decimal32 decimal32_t;
__extension__ typedef _Decimal64 decimal64_t;
__extension__ typedef _Decimal128 decimal28_t;
#elif defined(SROOK_HAS_DECIMAL_FLOATS)
typedef _Decimal32 decimal32_t;
typedef _Decimal64 decimal64_t;
typedef _Decimal128 decimal28_t
#endif

#if SROOK_ARCH_IS_ARM && SROOK_ARM_HAS_FP16
#   ifdef SROOK_GCC
__extension__ typedef __fp16 arm_fp16_t;
#   else
typedef __fp16 arm_fp16_t;
#   endif
#endif

} SROOK_NESTED_NAMESPACE_END(intrinsic_types, srook)
#endif
