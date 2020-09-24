// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_M68K_VERSION_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_M68K_VERSION_HPP
#include <srook/config/arch/M68K/core.hpp>
#if SROOK_ARCH_IS_M68K
#	if SROOK_MC68060
#		define SROOK_ARCH_M68K_VERSION 6.0
#	elif SROOK_MC68040
#		define SROOK_ARCH_M68K_VERSION 4.0
#	elif SROOK_MC68030
#		define SROOK_ARCH_M68K_VERSION 3.0
#	elif SROOK_MC68020
#		define SROOK_ARCH_M68K_VERSION 2.0
#	elif SROOK_MC68010
#		define SROOK_ARCH_M68K_VERSION 1.0
#	elif SROOK_MC68000
#		define SROOK_ARCH_M68K_VERSION 0.01
#	else
#		define SROOK_ARCH_M68K_VERSION 0.0
#	endif
#else
#	define SROOK_ARCH_M68K_VERSION 0.0
#endif
#endif
