// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CFENV_DISABLE_NAN_HPP
#define INCLUDED_SROOK_CFENV_DISABLE_NAN_HPP

#if defined (__i386__) || defined(__x86_64__)

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/cfenv/config.hpp>
#include <srook/cstdint.hpp>

SROOK_NESTED_NAMESPACE(srook, cfenv) {
SROOK_INLINE_NAMESPACE(v1)

SROOK_FORCE_INLINE void disable_nan()
{
    srook::uint16_t cw;
    asm volatile ("fnstcw %0":"=m"(cw));
    cw = static_cast<srook::uint16_t>(~(cw & 1u));
    asm volatile ("fldcw %0"::"m"(cw));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(cfenv, srook)
#else
#   error This feature needs the environment of x86_64
#endif
#endif
