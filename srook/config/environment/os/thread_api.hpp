// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_THREAD_API_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_THREAD_API_HPP

#include <srook/config/user_config.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/environment/os/endian.hpp>
#include <srook/config/environment/os/win.hpp>

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
#		ifdef __NetBSD__
#			pragma weak pthread_create
#		endif
#		if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#			include <sys/param.h>
#			ifdef BSD
#				include <sys/sysctl.h>
#			endif
#		endif
#		if defined(__unix__) || (defined(__APPLE__) &&\
	   	defined(__MACH__)) || defined(__CloudABI__) || defined(__Fuchsia__)
#			include <unistd.h>
#		endif
#		if defined(_POSIX_TIMEOUTS) &&\
		(_POSIX_TIMEOUTS - 200112L) >= 0L &&\
		(_POSIX_THREADS - 200112L) >= 0L
#			define SROOK_PTHREAD_TIMEOUTS_SUPPORT 1
#		else
#			define SROOK_PTHREAD_TIMEOUTS_SUPPORT 0
#		endif
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

#if !SROOK_CONFIG_DISABLE_THREAD_SAFETY_ANNOTATIONS &&\
	defined(__clang__) &&\
   	__has_cpp_attribute(acquire_capability) &&\
	!SROOK_OBJECT_FORMAT_IS_COFF
#		define SROOK_HAS_THREAD_SAFETY_ANNOTATIONS 1
#else
#		define SROOK_HAS_THREAD_SAFETY_ANNOTATIONS 0
#endif

#ifndef SROOK_HAS_CPP_ATTRIBUTE(require_constant_initialization)
#	define SROOK_SAFE_STATIC __attribute__((__require__constant_initialization__))
#else
#	define SROOK_SAFE_STATIC
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
