// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_COMPILER_MSVC_INTRIN_H
#define INCLUDED_SROOK_CONFIG_COMPILER_MSVC_INTRIN_H
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma onoce
#   endif
#   if _MSC_VER <= 1400
#       define _interlockedbittestandset(a, b) _interlockedbittestandset(volatile long*, long)
#       define _interlockedbittestandreset(a, b) _interlockedbittestandreset(volatile long*, long)
#       define _interlockedbittestandset64(a, b) _interlockedbittestandset(volatile long long*, long long)
#       define _interlockedbittestandreset64(a, b) _interlockedbittestandreset(volatile long long*, long long)
#   endif
#   include <intrin.h>
#   if _MSC_VER <= 1400
#       undef _interlockedbittestandreset
#       undef _interlockedbittestandset
#       undef _interlockedbittestandreset64
#       undef _interlockedbittestandset64
#   endif
#endif
#endif
