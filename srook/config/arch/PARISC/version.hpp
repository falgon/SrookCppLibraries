// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_PARISC_VERSION_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_PARISC_VERSION_HPP
#include <srook/config/arch/PARISC/core.hpp>

#if SROOK_ARCH_IS_PARISC
#	if SROOK_PA_RISC1_0
#		define SROOK_PARISC_VERSION 1.0
#	elif SROOK_PA_RISC1_1 && SROOK_HPPA11 && SROOK_PA7100
#		define SROOK_PARISC_VERSION 1.1
#	elif SROOK_PA_RISC2_0 && SROOK_RISC2_0 && SROOK_HPPA20 && SROOK_PA8000
#		define SROOK_PARISC_VERSION 2.0
#	else
#		define SROOK_PARISC_VERSION 0.0
#	endif
#else
#	define SROOK_PARISC_VERSION 0.0
#endif

#endif
