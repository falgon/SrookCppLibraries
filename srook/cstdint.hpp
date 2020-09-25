// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTDINT_HPP
#define INCLUDED_SROOK_CSTDINT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#ifndef __STDC_CONSTANT_MACROS
#   define __STDC_CONSTANT_MACROS
#endif

#include <srook/config/environment/os.hpp>
#if SROOK_HAS_INCLUDE(<boost/cstdint.hpp>)
#   include <boost/cstdint.hpp>
#   define SROOK_HAS_BOOST_CSTDINT_HPP 1
#endif

#if (defined(SROOK_HAS_STDINT_H) || defined(BOOST_HAS_STDINT_H))\
      && (!defined(__GLIBC__)\
      || defined(__GLIBC_HAVE_LONG_LONG)\
      || (defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 17)))))
#   ifdef __hpux
#       include <inttypes.h>
#           ifdef __STDC_32_MODE__
#               define SROOK_NO_INT64_T
#           endif
#   elif defined(__FreeBSD__) || defined(__IBMCPP__) || defined(_AIX)
#       include <inttypes.h>
#   else
#       include <stdint.h>
#       if defined(__STDC_CONSTANT_MACROS) && defined(__CYGWIN__)
#           undef INTMAX_C
#           undef UINTMAX_C
#           define INTMAX_C(c) c##LL
#           define UINTMAX_C(c) c##ULL
#       endif
#   endif

#   if defined(__QNX__) && defined(__EXT_QNX) && !defined(SROOK_HAS_BOOST_CSTDINT_HPP) && !defined(BOOST_CSTDINT_HPP)
typedef ::intleast8_t int_least8_t;
typedef ::intfast8_t int_fast8_t;
typedef ::uintleast8_t uint_least8_t;
typedef ::uintfast8_t uint_fast8_t;

typedef ::intleast16_t int_least16_t;
typedef ::intfast16_t int_fast16_t;
typedef ::uintleast16_t uint_least16_t;
typedef ::uintfast16_t uint_fast16_t;

typedef ::intleast32_t int_least32_t;
typedef ::intfast32_t int_fast32_t;
typedef ::uintleast32_t uint_least32_t;
typedef ::uintfast32_t uint_fast32_t;
#       if !defined(SROOK_NO_INT64_T) && !defined(BOOST_NO_INT64_T)
typedef ::intleast64_t int_least64_t;
typedef ::intfast64_t int_fast64_t;
typedef ::uintleast64_t uint_least64_t;
typedef ::uintfast64_t uint_fast64_t;
#       endif
#   endif

namespace srook {

using ::int8_t;
using ::int_least8_t;
using ::int_fast8_t;
using ::uint8_t;
using ::uint_least8_t;
using ::uint_fast8_t;
using ::int16_t;
using ::int_least16_t;
using ::int_fast16_t;
using ::uint16_t;
using ::uint_least16_t;
using ::uint_fast16_t;
using ::int32_t;
using ::int_least32_t;
using ::int_fast32_t;
using ::uint32_t;
using ::uint_least32_t;
using ::uint_fast32_t;

#ifndef SROOK_NO_INT64_T

using ::int64_t;
using ::int_least64_t;
using ::int_fast64_t;
using ::uint64_t;
using ::uint_least64_t;
using ::uint_fast64_t;

#endif

using ::intmax_t;
using ::uintmax_t;

} // namespace srook

#elif defined(__FreeBSD__) && (__FreeBSD__ <= 4) || defined(__osf__) || defined(__VMS) || defined(__SOLARIS9__) || defined(__NetBSD__)
#   include <inttypes.h>

namespace srook {

using ::int8_t;
typedef int8_t int_least8_t;
typedef int8_t int_fast8_t;
using ::uint8_t;
typedef uint8_t uint_least8_t;
typedef uint8_t uint_fast8_t;
using ::int16_t;
typedef int16_t int_least16_t;
typedef int16_t int_fast16_t;
using ::uint16_t;
typedef uint16_t uint_least16_t;
typedef uint16_t uint_fast16_t;
using ::int32_t;
typedef int32_t int_least32_t;
typedef int32_t int_fast32_t;
using ::uint32_t;
typedef uint32_t uint_least32_t;
typedef uint32_t uint_fast32_t;
#   ifndef SROOK_NO_INT64_T
using ::int64_t;
typedef int64_t int_least64_t;
typedef int64_t int_fast64_t;
using ::uint64_t;
typedef uint64_t uint_least64_t;
typedef uint64_t uint_fast64_t;
typedef int64_t intmax_t;
typedef uint64_t uintmax_t;
#   else
typedef int32_t intmax_t;
typedef uint32_t uintmax_t;
#   endif

} // namespace srook

#else

#   include <srook/limits/numeric_limits.hpp>
#   include <limits.h>
    #if SROOK_HAS_INCLUDE(<boost/limits.hpp>)
#       include <boost/limits.hpp>
#       define SROOK_HAS_BOOST_LIMITS_HPP 1
#   endif

namespace srook {

#   if UCHAR_MAX == 0xff
typedef signed char     int8_t;
typedef signed char     int_least8_t;
typedef signed char     int_fast8_t;
typedef unsigned char   uint8_t;
typedef unsigned char   uint_least8_t;
typedef unsigned char   uint_fast8_t;
#   else
#        error This environment is not supported
#   endif

#   if USHRT_MAX == 0xffff
#       ifdef __crayx1
typedef short           int16_t;
typedef short           int_least16_t;
typedef int             int_fast16_t;
typedef unsigned short  uint16_t;
typedef unsigned short  uint_least16_t; 
typedef unsigned int    uint_fast16_t;
#       else
typedef short           int16_t;
typedef short           int_least16_t;
typedef short           int_fast16_t;
typedef unsigned short  uint16_t;
typedef unsigned short  uint_least16_t;
typedef unsigned short  uint_fast16_t;
#       endif
#   elif (USHRT_MAX == 0xffffffff) && defined(__MTA__)
typedef __short16           int16_t;
typedef __short16           int_least16_t;
typedef __short16           int_fast16_t;
typedef unsigned __short16  uint16_t;
typedef unsigned __short16  uint_least16_t;
typedef unsigned __short16  uint_fast16_t;
#   elif (USHRT_MAX == 0xffffffff) && defined(CRAY)
typedef short           int_least16_t;
typedef short           int_fast16_t;
typedef unsigned short  uint_least16_t;
typedef unsigned short  uint_fast16_t;
#   else
#       error This environment is not supported
#   endif

#   if UINT_MAX == 0xffffffff
typedef int             int32_t;
typedef int             int_least32_t;
typedef int             int_fast32_t;
typedef unsigned int    uint32_t;
typedef unsigned int    uint_least32_t;
typedef unsigned int    uint_fast32_t;
#   elif (USHRT_MAX == 0xffffffff)
typedef short             int32_t;
typedef short             int_least32_t;
typedef short             int_fast32_t;
typedef unsigned short    uint32_t;
typedef unsigned short    uint_least32_t;
typedef unsigned short    uint_fast32_t;
#   elif ULONG_MAX == 0xffffffff
typedef long            int32_t;
typedef long            int_least32_t;
typedef long            int_fast32_t;
typedef unsigned long   uint32_t;
typedef unsigned long   uint_least32_t;
typedef unsigned long   uint_fast32_t;
#   elif (UINT_MAX == 0xffffffffffffffff) && defined(__MTA__)
typedef __int32           int32_t;
typedef __int32           int_least32_t;
typedef __int32           int_fast32_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int32  uint_least32_t;
typedef unsigned __int32  uint_fast32_t;
#   else
#       error This environment is not supported
#   endif

#   if (defined(SROOK_HAS_LONG_LONG) || defined(BOOST_HAS_LONG_LONG)) && \
   !defined(BOOST_MSVC) && !defined(__BORLANDC__) && \
   (!defined(__GLIBCPP__) || defined(_GLIBCPP_USE_LONG_LONG)) && \
   (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#       ifdef __hpux
#       elif (defined(ULLONG_MAX) && ULLONG_MAX == 18446744073709551615ULL) ||\
        (defined(ULONG_LONG_MAX) && ULONG_LONG_MAX == 18446744073709551615ULL) ||\
        (defined(ULONGLONG_MAX) && ULONGLONG_MAX == 18446744073709551615ULL)
#       else
#           error This environment is not supported
#       endif
#       ifdef SROOK_HAS_BOOST_CSTDINT_HPP
typedef  ::boost::long_long_type    intmax_t;
typedef  ::boost::ulong_long_type   uintmax_t;
typedef  ::boost::long_long_type    int64_t;
typedef  ::boost::long_long_type    int_least64_t;
typedef  ::boost::long_long_type    int_fast64_t;
typedef  ::boost::ulong_long_type   uint64_t;
typedef  ::boost::ulong_long_type   uint_least64_t;
typedef  ::boost::ulong_long_type   uint_fast64_t;
#       else
typedef  ::srook::long_long_type    intmax_t;
typedef  ::srook::ulong_long_type   uintmax_t;
typedef  ::srook::long_long_type    int64_t;
typedef  ::srook::long_long_type    int_least64_t;
typedef  ::srook::long_long_type    int_fast64_t;
typedef  ::srook::ulong_long_type   uint64_t;
typedef  ::srook::ulong_long_type   uint_least64_t;
typedef  ::srook::ulong_long_type   uint_fast64_t;
#       endif
#   elif ULONG_MAX != 0xffffffffUL
#       if ULONG_MAX == 18446744073709551615UL
typedef long                 intmax_t;
typedef unsigned long        uintmax_t;
typedef long                 int64_t;
typedef long                 int_least64_t;
typedef long                 int_fast64_t;
typedef unsigned long        uint64_t;
typedef unsigned long        uint_least64_t;
typedef unsigned long        uint_fast64_t;
#       else
#           error This environment is not supported
#       endif
#   elif defined(__GNUC__) && defined(BOOST_HAS_LONG_LONG)
__extension__ typedef long long            intmax_t;
__extension__ typedef unsigned long long   uintmax_t;
__extension__ typedef long long            int64_t;
__extension__ typedef long long            int_least64_t;
__extension__ typedef long long            int_fast64_t;
__extension__ typedef unsigned long long   uint64_t;
__extension__ typedef unsigned long long   uint_least64_t;
__extension__ typedef unsigned long long   uint_fast64_t;
#   elif defined(SROOK_HAS_MS_INT64) || defined(BOOST_HAS_MS_INT64)
typedef __int64             intmax_t;
typedef unsigned __int64    uintmax_t;
typedef __int64             int64_t;
typedef __int64             int_least64_t;
typedef __int64             int_fast64_t;
typedef unsigned __int64    uint64_t;
typedef unsigned __int64    uint_least64_t;
typedef unsigned __int64    uint_fast64_t;
#   else
#       define SROOK_NO_INT64_T
typedef int32_t intmax_t;
typedef uint32_t uintmax_t;
#   endif
} // namespace srook

#   if (defined(SROOK_OS_IS_WIN32) || defined(BOOST_WINDOWS)) && !defined(_WIN32_WCE) && (!defined(SROOK_HAS_STDINT_H) || !defined(BOOST_HAS_STDINT_H))
#       include <stddef.h>
#   endif

#   if ((defined(SROOK_OS_IS_WIN32) || defined(BOOST_WINDOWS)) && !defined(_WIN32_WCE)) ||\
        (defined(_XOPEN_UNIX) && (_XOPEN_UNIX+0 > 0) && !defined(__UCLIBC__)) ||\
        defined(__CYGWIN__) || defined(__VXWORKS__) ||\
        defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__) ||\
        defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || (defined(sun) && !defined(BOOST_HAS_STDINT_H)) || defined(INTPTR_MAX)
namespace srook {

using ::intptr_t;
using ::uintptr_t;

} // namespace srook
#       define SROOK_HAS_INTPTR_T 1
#   elif defined(__GNUC__) && defined(__INTPTR_TYPE__) && defined(__UINTPTR_TYPE__)

namespace srook {

typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

} // namespace srook

#       define SROOK_HAS_INTPTR_T 1
#   endif
#endif

#if !defined(BOOST__STDC_CONSTANT_MACROS_DEFINED) && \
    !defined(SROOK__STDC_CONSTANT_MACROS_DEFINED) &&\
    (!defined(INT8_C) || !defined(INT16_C) || !defined(INT32_C) || !defined(INT64_C))
#   if defined(__GNUC__) && (__GNUC__ >= 4)
#       pragma GCC system_header
#   endif
#   undef INT8_C
#   undef INT16_C
#   undef INT32_C
#   undef INT64_C
#   undef INTMAX_C
#   undef UINT8_C
#   undef UINT16_C
#   undef UINT32_C
#   undef UINT64_C
#   undef UINTMAX_C
#   include <limits.h>
#   define SROOK__STDC_CONSTANT_MACROS_DEFINED 1       
#   if defined(SROOK_HAS_MS_INT64) || defined(BOOST_HAS_MS_INT64)
#       ifndef INT8_C
#           define INT8_C(value)     value##i8
#       endif
#       ifndef INT16_C
#           define INT16_C(value)    value##i16
#       endif
#       ifndef INT32_C
#           define INT32_C(value)    value##i32
#       endif
#       ifndef INT64_C
#           define INT64_C(value)    value##i64
#       endif
#       ifdef __BORLANDC__
#           define UINT8_C(value)    static_cast<unsigned char>(value##u)
#       else
#           define UINT8_C(value)    value##ui8
#       endif
#       ifndef UINT16_C
#           define UINT16_C(value)   value##ui16
#       endif
#       ifndef UINT32_C
#           define UINT32_C(value)   value##ui32
#       endif
#       ifndef UINT64_C
#           define UINT64_C(value)   value##ui64
#       endif
#       ifndef INTMAX_C
#           define INTMAX_C(value)   value##i64
#           define UINTMAX_C(value)  value##ui64
#       endif
#   else
#       if (UCHAR_MAX == 0xff) && !defined(INT8_C)
#           define INT8_C(value) static_cast<srook::int8_t>(value)
#           define UINT8_C(value) static_cast<srook::uint8_t>(value##u)
#       endif
#       if (USHRT_MAX == 0xffff) && !defined(INT16_C)
#           define INT16_C(value) static_cast<srook::int16_t>(value)
#           define UINT16_C(value) static_cast<srook::uint16_t>(value##u)
#       endif
#       ifndef INT32_C
#           if (UINT_MAX == 0xffffffff)
#               define INT32_C(value) value
#               define UINT32_C(value) value##u
#           elif ULONG_MAX == 0xffffffff
#               define INT32_C(value) value##L
#               define UINT32_C(value) value##uL
#           endif
#       endif
#       ifndef INT64_C
#           if (defined(SROOK_HAS_LONG_LONG) || defined(BOOST_HAS_LONG_LONG)) && \
            (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX) || defined(_ULLONG_MAX) || defined(_LLONG_MAX))
#               ifdef __hpux
#                   define INT64_C(value) value##LL
#                   define UINT64_C(value) value##uLL
#           elif (defined(ULLONG_MAX) && ULLONG_MAX == 18446744073709551615ULL) ||  \
            (defined(ULONG_LONG_MAX) && ULONG_LONG_MAX == 18446744073709551615ULL) ||  \
            (defined(ULONGLONG_MAX) && ULONGLONG_MAX == 18446744073709551615ULL) || \
            (defined(_ULLONG_MAX) && _ULLONG_MAX == 18446744073709551615ULL) || \
            (defined(_LLONG_MAX) && _LLONG_MAX == 9223372036854775807LL)
#               define INT64_C(value) value##LL
#               define UINT64_C(value) value##uLL
#           else
#               error This environment is not supported
#           endif
#       elif ULONG_MAX != 0xffffffff
#           if ULONG_MAX == 18446744073709551615U
#               define INT64_C(value) value##L
#               define UINT64_C(value) value##uL
#           else
#               error This environment is not supported
#           endif
#       endif
#   elif defined(SROOK_HAS_LONG_LONG) || defined(BOOST_HAS_LONG_LONG)
#       if (~0uLL == 18446744073709551615ULL)
#           define INT64_C(value) value##LL
#           define UINT64_C(value) value##uLL
#       else
#           error This environment is not supported
#       endif
#   else
#       error This environment is not supported
#   endif

#   if defined(SROOK_NO_INT64_T) || defined(BOOST_NO_INT64_T)
#       define INTMAX_C(value) INT32_C(value)
#       define UINTMAX_C(value) UINT32_C(value)
#   else
#       define INTMAX_C(value) INT64_C(value)
#       define UINTMAX_C(value) UINT64_C(value)
#   endif
#endif
#endif

#if defined(SROOK_HAS_INT128) && !defined(__STRICT_ANSI__)
namespace srook {

#ifdef SROOK_GCC
__extension__ typedef __int128 int128_t;
__extension__ typedef unsigned __int128 uint128_t;
#else
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t; 
#endif

} // namespace srook
#endif

#endif // include gurad
