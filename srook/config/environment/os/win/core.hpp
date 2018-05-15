// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_CONFIG_ENVIRONMENT_OS_WIN_CORE_HPP
#define INCLUDED_SROOK_CONFIG_CONFIG_ENVIRONMENT_OS_WIN_CORE_HPP

#if defined(_WIN32) || defined(__WIN32__) || defined(_MSC_VER)
#	define SROOK_OS_IS_WIN32 1
#	define SROOK_OS_WIN32 SROOK_OS_IS_WIN32
#	define SROOK_OBJECT_FORMAT_IS_COFF 1
#   include <srook/config/compiler/msvc/includes/windows.h>
#	include <windows.h>
#	include <stdio.h>
#	include <tchar.h>
#	if defined(__CYGWIN32__) || defined(__CYGWIN__)
#		define SROOK_OS_CYGWIN 1
#	else
#		define SROOK_OS_CYGWIN 0
#	endif
#else
#	define SROOK_OS_IS_WIN32 0
#	define SROOK_OS_WIN32 SROOK_OS_IS_WIN32
#	define SROOK_OBJECT_FORMAT_IS_COFF 0
#	define SROOK_OS_CYGWIN 0
#endif

#endif
