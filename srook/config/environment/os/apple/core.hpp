// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ENVIRONMENT_OS_APPLE_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ENVIRONMENT_OS_APPLE_CORE_HPP

#if defined(_LIBCPP_USE_AVAILABILITY_APPLE) || defined(__APPLE__) || defined(__MACH__) || defined(Macintosh) || defined(macintosh)
#	define SROOK_APPLE 1
#	include <sys/attr.h>
#	include <sys/types.h>
#	include <sys/uio.h>
#	include <sys/errno.h>
#	include <fcntl.h>
#	include <signal.h>
#	include <unistd.h>
#	include <cstdlib>
#	include <cstdio>
#	include <cstring>
#else
#	define SROOK_APPLE 0
#endif

#if defined(__APPLE__) && defined(__MACH__) && defined(macintosh) && defined(Macintosh)
#	define SROOK_OS_MACOS 1
#else
#	define SROOK_OS_MACOS 0
#endif

#if defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#	define SROOK_OS_IOS 1
#	define SROOK_OS_IOS_ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED * 1000
#else
#	define SROOK_OS_IOS 0
#	define SROOK_OS_IOS_ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED 0
#endif

#endif
