// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_PPC_CORE_HPP
#define INCLUDED_SROOK_CONFIG_PPC_CORE_HPP
#if defined(__powerpc) ||\
   	defined(__powerpc__) ||\
	defined(__POWERPC__) ||\
	defined(__ppc__) ||\
	defined(_M_PPC) ||\
	defined(_ARCH_PPC) ||\
	defined(__PPCGECKO__) ||\
   	defined(__PPCBROADWAY__) ||\
   	defined(_XENON) ||\
    defined(__ppc64__) ||\
    defined(__PPC64__) ||\
    defined(_ARCH_PPC64) ||\
    defined(__powerpc64__)
#   if defined(__ppc64__) || defined(__PPC64__) || defined(__powerpc64__) || defined(_ARCH_PPC64)
#       define SROOK_ARCH_IS_PPC64 1
#   else
#	    define SROOK_ARCH_IS_PPC 1
#   endif
#	if defined(_ARCH_440)
#		define SROOK_ARCH_PPC440 440
#	else
#		define SROOK_ARCH_PPC440 0
#	endif
#	if defined(_ARCH_450)
#		define SROOK_ARCH_PPC450 450
#	else
#		define SROOK_ARCH_PPC450 0
#	endif
#	if defined(__ppc601__)
#		define SROOK_ARCH_PPC601 __ppc601__
#	elif defined(_ARCH_601)
#		define SROOK_ARCH_PPC601 _ARCH_601
#	else
#		define SROOK_ARCH_PPC601 0
#	endif
#	if defined(__ppc603__)
#		define SROOK_ARCH_PPC603 __ppc603__
#	elif defined(_ARCH_603)
#		define SROOK_ARCH_PPC603 _ARCH_603
#	else
#		define SROOK_ARCH_PPC603 0
#	endif
#	if defined(__ppc604__)
#		define SROOK_ARCH_PPC604 __ppc604__
#	elif defined(_ARCH_604)
#		define SROOK_ARCH_PPC604 _ARCH_604
#	else
#		define SROOK_ARCH_PPC604 0
#	endif
#	if !SROOK_ARCH_440 && !SROOK_ARCH_450 && !SROOK_ARCH_PPC601 && !SROOK_ARCH_PPC603 && !SROOK_ARCH_PPC604
#		define SROOK_ARCH_PPC620 620
#	else
#		define SROOK_ARCH_PPC620 0
#	endif
#else
#	define SROOK_ARCH_IS_PPC 0
#   define SROOK_ARCH_IS_PPC64 0
#	define SROOK_ARCH_440 0
#	define SROOK_ARCH_450 0
#	define SROOK_ARCH_PPC601 0
#	define SROOK_ARCH_PPC603 0
#	define SROOK_ARCH_PPC604 0
#	define SROOK_ARCH_PPC620
#endif
#endif
