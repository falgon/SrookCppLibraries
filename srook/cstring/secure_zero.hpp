// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTRING_SECURE_ZERO_HPP
#define INCLUDED_SROOK_CSTRING_SECURE_ZERO_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#ifdef _WIN32
#   include <srook/config/compiler/includes/msvc/windows.h>
#   define SROOK_SECURE_ZERO(X, S) SecureZeroMemory(X, S)
#elif  __STDC_VERSION__ >= 201112L && defined(__STDC_LIB_EXT1__)
#   ifndef __STDC_WANT_LIB_EXT1__
#       define __STDC_WANT_LIB_EXT1__ 1
#   endif
extern "C" {
#   include <string.h>
};
#   define SROOK_SECURE_ZERO(X, S) ::memset_s(X, S, 0, S)
#elif (defined(__unix__) && (defined(__FreeBSD__)) && !defined(USG)) || defined(HAVE_SYS_PARAM_H)
extern "C" {
#   include <sys/param.h>
#   include <osreldate.h>
};
#   if __FreeBSD_version >= 1100000
extern "C" {
#       include <string.h>
};
#       define SROOK_SECURE_ZERO(X, S) ::explicit_bzero(X, S)
#   endif
#endif
#ifndef SROOK_SECURE_ZERO
#   if defined(__unix__) && defined(__OpenBSD__) && !defined(USG)
extern "C" {
#       include <sys/param.h>
};
#       if defined(BSD) && BSD >= 500000
extern "C" {
#           include <string.h>
};
#           define SROOK_SECURE_ZERO(X, S) ::explicit_bzero(X, S)
#       endif
#   endif
#endif
#ifndef SROOK_SECURE_ZERO
#include <cstring>
SROOK_NESTED_NAMESPACE(srook, cstring) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

#ifdef SROOK_ATTRIBUTE_WEAK
SROOK_ATTRIBUTE_WEAK void explicit_zero_hook(void*, std::size_t) { }
void memset_s(void* buf, std::size_t len)
{
    std::memset(buf, 0, len);
    explicit_zero_hook(buf, len);
}
#else
void memset_s(void* buf, std::size_t len)
{
    volatile char* p = static_cast<volatile char*>(buf);
    while (n--) *p++ = SROOK_NULLPTR;
}
#endif

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(cstring, srook)
#endif

SROOK_NESTED_NAMESPACE(srook, cstring) {
SROOK_INLINE_NAMESPACE(v1)

SROOK_FORCE_INLINE void secure_zero(void* buf, std::size_t len)
{
#ifdef SROOK_SECURE_ZERO
    SROOK_SECURE_ZERO(buf, len);
#else
    detail::memset_s(buf, len);
#endif
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(cstring, srook)

#endif
