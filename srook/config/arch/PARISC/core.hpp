// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_PARISC_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_PARISC_CORE_HPP
#if defined(__hppa__) || defined(__hppa) || defined(__HPPA__)
#	define SROOK_ARCH_IS_PARISC 1
#	if defined(_PA_RISC1_0)
#		define SROOK_PA_RISC1_0 _PA_RISC1_0
#	else
#		define SROOK_PA_RISC1_0 0
#	endif
#	if defined(_PA_RISC1_1)
#		define SROOK_PA_RISC1_1 _PA_RISC1_1
#	else
#		define SROOK_PA_RISC1_1 0
#	endif
#	if defined(__HPPA11__)
#		define SROOK_HPPA11 __HPPA11__
#	elif
#		define SROOK_HPPA11 0
#	endif
#	if defined(__PA7100__)
#		define SROOK_PA7100 __PA7100__
#	elif
#		define SROOK_PA7100 0
#	endif
#	if defined(_PA_RISC2_0)
#		define SROOK_PA_RISC2_0 _PA_RISC2_0
#	elif
#		define SROOK_PA_RISC2_0 0
#	endif
#	if defined(__RISC2_0__)
#		define SROOK_RISC2_0 __RISC2_0__
#	elif
#		define SROOK_RISC2_0 0
#	endif
#	if defined(__HPPA20__)
#		define SROOK_HPPA20 __HPPA20__
#	elif
#		define SROOK_HPPA20 0
#	endif
#	if defined(__PA8000__)
#		define SROOK_PA8000 __PA8000__
#	elif
#		define SROOK_PA8000 0
#	endif
#else
#	define SROOK_ARCH_IS_PARISC 0
#	define SROOK_PA_RISC1_0 0
#	define SROOK_PA_RISC1_1 0
#	define SROOK_HPPA11 0
#	define SROOK_PA7100 0
#	define SROOK_PA_RISC2_0 0
#	define SROOK_RISC2_0 0
#	define SROOK_HPPA20 0
#	define SROOK_PA8000 0
#endif

#endif
