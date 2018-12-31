// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_SUPERH_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_SUPERH_CORE_HPP

#if defined(__sh__)
#	define SROOK_ARCH_IS_SUPERH 1
#	if defined(__SH5__)
#		define SROOK_ARCH_SH5 __SH5__
#	else
#		define SROOK_ARCH_SH5 0
#	endif
#	if defined(__SH4__)
#		define SROOK_ARCH_SH4 __SH4__
#	else
#		define SROOK_ARCH_SH4 0
#	endif
#	if defined(__sh3__)
#		define SROOK_ARCH_SH3 __sh3__
#	elif defined(__SH3__)
#		define SROOK_ARCH_SH3 __SH3__
#	else
#		define SROOK_ARCH_SH3 0
#	endif
#	if defined(__sh2__)
#		define SROOK_ARCH_SH2 __sh2__
#	else
#		define SROOK_ARCH_SH2 0
#	endif
#	if defined(__sh1__)
#		define SROOK_ARCH_SH1 __sh1__
#	else
#		define SROOK_ARCH_SH1 0
#	endif
#else
#	define SROOK_ARCH_IS_SUPERH 0
#	define SROOK_ARCH_SH5 0
#	define SROOK_ARCH_SH4 0
#	define SROOK_ARCH_SH3 0
#	define SROOK_ARCH_SH2 0
#	define SROOK_ARCH_SH1 0
#endif

#endif
