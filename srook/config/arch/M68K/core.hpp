// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_M68K_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_M68K_CORE_HPP

#if defined(__m68k__) || defined(M68000)
#	define SROOK_ARCH_IS_M68K 1
#	if defined(__mc68060__)
#		define SROOK_MC68060 __mc68060__
#	elif defined(mc68060)
#		define SROOK_MC68060 mc68060
#	elif defined(__mc68060)
#		define SROOK_MC68060 __mc68060
#	else
#		define SROOK_MC68060 0
#	endif
#	if defined(__mc68040__)
#		define SROOK_MC68040 __mc68040__
#	elif defined(mc68040)
#		define SROOK_MC68040 mc68040
#	elif defined(__mc68040) __mc68040
#		define SROOK_MC68040 __mc68040
#	else
#		define SROOK_MC68040 0
#	endif
#	if defined(__mc68030__)
#		define SROOK_MC68030 __mc68030__
#	elif defined(mc68030)
#		define SROOK_MC68030 mc68030
#	elif defined(__mc68030)
#		define SROOK_MC68030 __mc68030
#	else
#		define SROOK_MC68030 0
#	endif
#	if defined(__mc68020__)
#		define SROOK_MC68020 __mc68020__
#	elif defined(mc68020)
#		define SROOK_MC68020 mc68020
#	elif defined(__mc68020)
#		define SROOK_MC68020 __mc68020
#	else
#		define SROOK_MC68020 0
#	endif
#	if defined(__mc68010__)
#		define SROOK_MC68010 __mc68010__
#	elif defined(mc68010)
#		define SROOK_MC68010 mc68010
#	elif defined(__mc68010)
#		define SROOK_MC68010 __mc68010
#	else
#		define SROOK_MC68010 0
#	endif
#	if defined(__mc68000__)
#		define SROOK_MC68000 __mc68000__
#	elif defined(mc68000)
#		define SROOK_MC68000 mc68000
#	elif defined(__mc68000)
#		define SROOK_MC68000 __mc68000
#	else
#		define SROOK_MC68000 0
#	endif
#else
#	define SROOK_ARCH_IS_M68K 0
#	define SROOK_MC68060 0
#	define SROOK_MC68040 0
#	define SROOK_MC68030 0
#	define SROOK_MC68020 0
#	define SROOK_MC68010 0
#	define SROOK_MC68000 0
#endif

#endif
