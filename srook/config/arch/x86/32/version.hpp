// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_X86_32_VERSION_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_X86_32_VERSION_HPP
#include <srook/config/arch/x86/32/core.hpp>
#if defined(SROOK_ARCH_IS_X86_32)
#	if SROOK_ARCH_I686
#		define SROOK_ARCH_X86_32_VERSION 6.0.0
#	elif SROOK_ARCH_I586
#		define SROOK_ARCH_X86_32_VERSION 5.0.0
#	elif SROOK_ARCH_I486
#		define SROOK_ARCH_X86_32_VERSION 4.0.0
#	elif SROOK_ARCH_I386
#		define SROOK_ARCH_X86_32_VERSION 3.0.0
#	else
#		define SROOK_ARCH_X86_32_VERSION SROOK_ARCH_I86
#	endif
#else
#	define SROOK_ARCH_X86_32_VERSION 0
#endif
#endif
