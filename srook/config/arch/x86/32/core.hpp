// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ARCH_X86_32_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_X86_32_CORE_HPP
#if defined(i386) || \
	defined(__i386__) ||\
	defined(__i486__) ||\
	defined(__i586__) ||\
	defined(__i686__) ||\
	defined(__i386) ||\
	defined(_M_IX86) ||\
	defined(_X86_) ||\
	defined(__THW_INTEL__) ||\
	defined(__I86__) ||\
	defined(__INTEL__)
#	define SROOK_ARCH_IS_X86_32 1
#	if defined(__I86__)
#		define SROOK_ARCH_I86 __I86__
#	else
#		define SROOK_ARCH_I86 0
#	endif
#	if defined(SROOK_ARCH_I86) && defined(_M_IX86)
#		define SROOK_ARCH_I86 _M_IX86
#	else
#		define SROOK_ARCH_I86 0
#	endif
#	if defined(__i686__)
#		define SROOK_ARCH_I686 __i686__
#	else
#		define SROOK_ARCH_I686 0
#	endif
#	if defined(__i586__)
#		define SROOK_ARCH_I586 __i586__
#	else
#		define SROOK_ARCH_I586 0
#	endif
#	if defined(__i486__)
#		define SROOK_ARCH_I486 __i486__
#	else
#		define SROOK_ARCH_I486 0
#	endif
#	if defined(__i386__)
#		define SROOK_ARCH_I386 __i386__
#	else
#		define SROOK_ARCH_I386 0
#	endif
#else
#	define SROOK_ARCH_IS_X86_32 0
#	define SROOK_ARCH_I86 0
#	define SROOK_ARCH_I686 0
#	define SROOK_ARCH_I586 0
#	define SROOK_ARCH_I486 0
#	define SROOK_ARCH_I386 0
#endif
#endif
