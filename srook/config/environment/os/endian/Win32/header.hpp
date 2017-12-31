// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_WIN32_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_WIN32_HPP

#include <srook/config/arch.hpp>

#ifdef _WIN32
#	define SROOK_WIN32API 1
#	define SROOK_LITTLE_ENDIAN 1
#	define SROOK_BIG_ENDIAN 0
#	define SROOK_SHORT_WCHAR 1
#	if defined(_MSC_VER) && !defined(__MINGW32__)
#		define SROOK_USE_MSVCRT 1
#		define SROOK_HAS_QUICK_EXIT 1
#	else
#		define SROOK_USE_MSVCRT 0
#		define SROOK_HAS_QUICK_EXIT 0
#	endif
#	if SROOK_ARCH_IS_AMD64 || SROOK_ARCH_IS_x86_64 || SROOK_ARCH_IS_ARM || SROOK_ARCH_IS_ARM64
#		define SROOK_HAS_BITSCAN64 1
#	else
#		define SROOK_HAS_BITSCAN64 0
#	endif
#else
#	define SROOK_WIN32API 0
#	define SROOK_USE_MSVCRT 0
#	define SROOK_HAS_BITSCAN64 0
#	define SROOK_HAS_QUICK_EXIT 0
#	define SROOK_SHORT_WCHAR 0
#endif

#endif
