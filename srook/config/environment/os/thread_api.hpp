// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_THREAD_API_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_THREAD_API_HPP

#include <srook/config/user_config.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/environment/os/endian.hpp>

#if !defined(SROOK_CONFIG_NO_THREADS) &&\
	!defined(SROOK_HAS_THREADS) &&\
	!defined(SROOK_HAS_THREAD_API_PTHREAD) &&\
	!defined(SROOK_HAS_THREAD_API_WIN32) &&\
	!defined(SROOK_HAS_THREAD_API_EXTERNAL)
#	if defined(__FreeBSD__) ||\
	   	defined(__Fuchsia__) ||\
	   	defined(__NetBSD__) ||\
	   	defined(__linux__) ||\
	   	defined(__APPLE__) ||\
		defined(__CloudABI__) ||\
		defined(__sun__) ||\
		(defined(__MINGW32__) && SROOK_HAS_INCLUDE(<pthread.h>))
#		define SROOK_HAS_THREADS 1
#		define SROOK_HAS_THREAD_API_PTHREAD 1
#		define SROOK_HAS_THREAD_API_WIN32 0
#		define SROOK_HAS_THREAD_API_EXTERNAL 0
#	elif defined(SROOK_WIN32API)
#		define SROOK_HAS_THREADS 1
#		define SROOK_HAS_THREAD_API_PTHREAD 0
#		define SROOK_HAS_THREAD_API_WIN32 1
#		define SROOK_HAS_THREAD_API_EXTERNAL 0
#	else
#		define SROOK_HAS_THREADS 0
#		define SROOK_HAS_THREAD_API_PTHREAD 0
#		define SROOK_HAS_THREAD_API_WIN32 0
#		define SROOK_HAS_THREAD_API_EXTERNAL 0
#	endif
#endif

#ifdef __clang__
#	ifdef _LIBCPP_HAS_C_ATOMIC_IMP
#		define SROOK_HAS_C_ATOMIC_IMP 1
#	elif defined(_LIBCPP_HAS_GCC_ATOMIC_IMP)
#		define SROOK_HAS_GCC_ATOMIC_IMP 1
#	endif
#else
#	if defined(__has_feature)
#		if __has_feature(cxx_atomic)
#			define SROOK_HAS_C_ATOMIC_IMP 1
#		endif
#		if _GNUC_VER > 407
#			define SROOK_HAS_GCC_ATOMIC_IMP 1
#		endif
#	elif defined(__has_extension)
#		if __has_extension(c_atomic)
#			define SROOK_HAS_C_ATOMIC_IMP 1
#		endif
#		if _GNUC_VER > 407
#			define SROOK_HAS_GCC_ATOMIC_IMP 1
#		endif
#	elif defined(__has_keyword)
#		if __has_keyword(_Atomic)
#			define SROOK_HAS_C_ATOMIC_IMP 1
#		endif
#		if _GNUC_VER > 407
#			define SROOK_HAS_GCC_ATOMIC_IMP 1
#		endif
#	endif
#endif

#ifndef SROOK_HAS_C_ATOMIC_IMP
#	define SROOK_HAS_C_ATOMIC_IMP 0
#endif
#ifndef SROOK_HAS_GCC_ATOMIC_IMP
#	define SROOK_HAS_GCC_ATOMIC_IMP 0
#endif

#include <srook/config/environment/os/apple.hpp>
#ifdef __clang__
#	ifdef _LIBCPP_AVAILABILITY_SHARED_MUTEX
#		define SROOK_APPLE_AVALAIBILITY_SHARED_MUTEX 1
#	endif
#elif defined(SROOK_APPLE)
#	define SROOK_APPLE_AVALAIBILITY_SHARED_MUTEX \
	__attribute__((availability(macosx, strict, introduced=10.12)))\
	__attribute__((availability(ios, strict, introduced=10.0)))\
	__attribute__((availability(tvos, strict, introduced=10.0)))\
	__attribute__((availability(watchos, strict, introduced=3.0)))
#endif

#ifndef SROOK_AVALAIBILITY_SHARED_MUTEX
#	define SROOK_APPLE_AVALAIBILITY_SHARED_MUTEX
#endif

#endif
