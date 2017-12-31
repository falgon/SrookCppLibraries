// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_MIPS_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_MIPS_CORE_HPP

#if defined(__mips__) || defined(__mips) || defined(__MIPS__)
#	define SROOK_ARCH_IS_MIPS 1
#	if defined(_MIPS_ISA_MIPS1)
#		define SROOK_ARCH_MIPS_VERSION _MIPS_ISA_MIPS1
#	elif defined(_R3000)
#		define SROOK_ARCH_MIPS_VERSION _R3000
#	elif defined(_MIPS_ISA_MIPS2)
#		define SROOK_ARCH_MIPS_VERSION _MIPS_ISA_MIPS2
#	elif defined(__MIPS_ISA2__)
#		define SROOK_ARCH_MIPS_VERSION __MIPS_ISA2__
#	elif defined(_R4000)
#		define SROOK_ARCH_MIPS_VERSION _R4000
#	elif defined(_MIPS_ISA_MIPS3)
#		define SROOK_ARCH_MIPS_VERSION _MIPS_ISA_MIPS3
#	elif defined(__MIPS_ISA3__)
#		define SROOK_ARCH_MIPS_VERSION __MIPS_ISA3__
#	elif defined(_MIPS_ISA_MIPS4)
#		define SROOK_ARCH_MIPS_VERSION _MIPS_ISA_MIPS4
#	elif defined(__MIPS_ISA4__)
#		define SROOK_ARCH_MIPS_VERSION __MIPS_ISA4__
#	else
#		define SROOK_ARCH_MIPS_VERSION __mips
#	endif
#else
#	define SROOK_ARCH_IS_MIPS 0
#	define SROOK_ARCH_MIPS_VERSION 0
#endif

#endif
