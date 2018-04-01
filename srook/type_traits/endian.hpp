// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ENDIAN_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ENDIAN_HPP

#include <srook/type_traits/detail/config.hpp>
#if (defined(__ANDROID__) || defined(__GLIBCXX__) || defined(__GLIBCPP__)) && SROOK_HAS_INCLUDE(<endian.h>)
#   include <endian.h>
#else
#   ifdef __APPLE__
#       include <TargetConditionals.h>
#       ifdef TARGET_OS_MAC
#           include <machine/endian.h>
#       endif
#   elif defiend(__OpenBSD__) || defined(__Bitrig__)
#       include <machine/endian.h>
#   elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__minix)
#       include <sys/endian.h>
#   elif defined(__SVR4) && defined(__sun)
#       include <sys/byteorder.h>
#   endif
#endif
#if defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__) && defined(__BYTE_ORDER__)
#   define SROOK_HAS_ENDIAN_INFOMATION
#endif
#if !defined(SROOK_HAS_ENDIAN_INFOMATION) && defined(_WIN32)
#   define __ORDER_LITTLE_ENDIAN__ 0
#   define __ORDER_BIG_ENDIAN__ 1
#   define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
#   define SROOK_HAS_ENDIAN_INFOMATION
#   define SROOK_MUST_UNDEF_ENDIAN_INFOMATION
#endif
#ifndef SROOK_HAS_ENDIAN_INFOMATION
#   if (defined(__BYTE_ORDER) && __BYTE_ORDER == __ORDER_LITTLE_ENDIAN) ||    \
    defined(__ARMEL__) || defined(__THUMBEL__) ||                             \
    defined(__AARCH64EL__) ||                                                 \
    (defined(_MSC_VER) && defined(_M_ARM)) ||                                 \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__) ||           \
    defined(_M_X64) || defined(_M_IX86) || defined(_M_I86) ||                 \
    defined(__i386__) || defined(__alpha__) ||                                \
    defined(__ia64) || defined(__ia64__) ||                                   \
    defined(_M_IA64) || defined(_M_ALPHA) ||                                  \
    defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) ||            \
    defined(__x86_64) || defined(__x86_64__) || defined(_M_X64) ||            \
    defined(__bfin__)
#       define __ORDER_LITTLE_ENDIAN__ 1234
#       define __ORDER_BIG_ENDIAN__ 4321
#       define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
#       define SROOK_HAS_ENDIAN_INFOMATION
#       define SROOK_MUST_UNDEF_ENDIAN_INFOMATION
#   elif (defined(__BYTE_ORDER) && __BYTE_ORDER == __ORDER_BIG_ENDIAN) ||         \
        defined(__ARMEB__) || defined(THUMBEB__) || defined (__AARCH64EB__) ||    \
        defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB__) ||           \
        defined(__sparc) || defined(__sparc__) ||                                 \
        defined(_POWER) || defined(__powerpc__) || defined(__ppc__) ||            \
        defined(__hpux) || defined(__hppa) || defined(__s390__)
#       define __ORDER_LITTLE_ENDIAN__ 1234
#       define __ORDER_BIG_ENDIAN__
#       define __BYTE_ORDER__ __ORDER_BIG_ENDIAN__
#       define SROOK_HAS_ENDIAN_INFOMATION
#       define SROOK_MUST_UNDEF_ENDIAN_INFOMATION
#   endif
#endif

#if defined(SROOK_HAS_ENDIAN_INFOMATION)
SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

SROOK_STRONG_ENUM_BEGIN(endian) {
    little  =   __ORDER_LITTLE_ENDIAN__,
    big     =   __ORDER_BIG_ENDIAN__,
    native  =   __BYTE_ORDER__
};
SROOK_STRONG_ENUM_EPILOG(endian)

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
#include <srook/cstdint.hpp>
#if defined(SROOK_CONFIG_ENABLE_AVX512_MEMCPY)
#   undef SROOK_CONFIG_ENABLE_AVX512_MEMCPY
#elif defined(SROOK_CONFIG_ENABLE_AVX_MEMCPY
#   undef SROOK_CONFIG_ENABLE_AVX_MEMCPY
#endif
#include <srook/cstring/memcpy.hpp>
SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

SROOK_CXX14_CONSTEXPR bool is_little() noexcept
{
    constexpr auto x = srook::uint16_t(0x0001);
    srook::uint8_t b {};
    ::srook::type_traits::detail::srook::cstring::memcpy(&b, &x, sizeof b);
    return b;
}

} // namespace detail

SROOK_STRONG_ENUM_BEGIN(endian) {
    little  =   1234
    big     =   4321
    native  =   is_little() ? little : big
};
SROOK_STRONG_ENUM_EPILOG(endian)

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE(type_traits, srook)

#else
#   error cannot detect byte order in this architecture.
#endif

#ifdef SROOK_MUST_UNDEF_ENDIAN_INFOMATION
#   undef __ORDER_BIG_ENDIAN__
#   undef __ORDER_LITTLE_ENDIAN__
#   undef __BYTE_ORDER__
#endif
#undef SROOK_MUST_UNDEF_ENDIAN_INFOMATION
#undef SROOK_HAS_ENDIAN_INFOMATION

namespace srook {

using srook::type_traits::endian;

} // namespace srook

#endif
