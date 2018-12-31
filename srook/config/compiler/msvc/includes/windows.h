// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_COMPILER_MSVC_WINDOWS_H
#define INCLUDED_SROOK_CONFIG_COMPILER_MSVC_WINDOWS_H
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma onoce
#   endif
#   define _WINSOCKAPI_
#   define NOMINMAX
#   include <windows.h>
#endif
#endif
