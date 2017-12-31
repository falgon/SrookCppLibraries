// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
// Reference: http://infocenter.arm.com/help/topic/com.arm.doc.dui0376d/DUI0376D_compiler_reference.pdf
#include <srook/config/user_config.hpp>

#ifndef INCLUDED_SROOK_CONFIG_ARCH_ARM_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_ARM_CORE_HPP
#if defined(__arm__) ||\
   	defined(__thumb__) ||\
	defined(_ARM) ||\
	defined(_M_ARM) ||\
	defined(_M_ARM64) ||\
	defined(_M_ARMT) ||\
	defined(__arm) ||\
	defined(__TARGET_ARCH_ARM) ||\
	defined(__TARGET_ARCH_THUMB)
#	define SROOK_ARCH_IS_ARM 1
#	define SROOK_TARGET_ARCH_ARM __TARGET_ARCH_ARM
#	if defined(__ARM_ARCH_2__)
#		define SROOK_ARM_ARCH_2 __ARM_ARCH_2__
#	else
#		define SROOK_ARM_ARCH_2 0
#	endif
#	if defined(__ARM_ARCH_3__)
#		define SROOK_ARM_ARCH_3 __ARM_ARCH_3__
#	else
#		define SROOK_ARM_ARCH_3 0
#	endif
#	if defined(__ARM_ARCH_3M__)
#		define SROOK_ARM_ARCH_3M __ARM_ARCH_3M__
#	else
#		define SROOK_ARM_ARCH_3M 0
#	endif
#	if defined(__ARM_ARCH_4__)
#		define SROOK_ARM_ARCH_4 __ARM_ARCH_4__
#	else
#		define SROOK_ARM_ARCH_4 0
#	endif
#	if defined(__ARM_ARCH_4T__)
#		define SROOK_ARM_ARCH_4T __ARM_ARCH_4T__
#	else
#		define SROOK_ARM_ARCH_4T 0
#	endif
#	if defined(__ARM_ARCH_5__)
#		define SROOK_ARM_ARCH_5 __ARM_ARCH_5__
#	else
#		define SROOK_ARM_ARCH_5 0
#	endif
#	if defined(__ARM_ARCH_5E__)
#		define SROOK_ARM_ARCH_5E __ARM_ARCH_5E__
#	else
#		define SROOK_ARM_ARCH_5E 0
#	endif
#	if defined(__ARM_ARCH_5T__)
#		define SROOK_ARM_ARCH_5T __ARM_ARCH_5T__
#	else
#		define SROOK_ARM_ARCH_5T 0
#	endif
#	if defined(__ARM_ARCH_5TE__)
#		define SROOK_ARM_ARCH_5TE __ARM_ARCH_5TE__
#	else
#		define SROOK_ARM_ARCH_5TE 0
#	endif
#	if defined(__ARM_ARCH_5TEJ__)
#		define SROOK_ARM_ARCH_5TEJ __ARM_ARCH_5TEJ__
#	else
#		define SROOK_ARM_ARCH_5TEJ 0
#	endif
#	if defined(SROOK_ARM_ARCH_6)
#		define SROOK_ARM_ARCH_6 __ARM_ARCH_6__
#	else
#		define SROOK_ARM_ARCH_6 0
#	endif
#	if defined(SROOK_ARM_ARCH_6J)
#		define SROOK_ARM_ARCH_6J __ARM_ARCH_6J__
#	else
#		define SROOK_ARM_ARCH_6J 0
#	endif
#	if defined(SROOK_ARM_ARCH_6K)
#		define SROOK_ARM_ARCH_6K __ARM_ARCH_6K__
#	else
#		define SROOK_ARM_ARCH_6K 0
#	endif
#	if defined(SROOK_ARM_ARCH_6Z)
#		define SROOK_ARM_ARCH_6Z __ARM_ARCH_6Z__
#	else
#		define SROOK_ARM_ARCH_6Z 0
#	endif
#	if defined(SROOK_ARM_ARCH_6ZK)
#		define SROOK_ARM_ARCH_6ZK __ARM_ARCH_6ZK__
#	else
#		define SROOK_ARM_ARCH_6ZK 0
#	endif
#	if defined(__ARM_ARCH_6T2__)
#		define SROOK_ARM_ARCH_6T2 __ARM_ARCH_6T2__
#	endif
#	if defined(__ARM_ARCH_7__)
#		define SROOK_ARM_ARCH_7 __ARM_ARCH_7__
#	endif
#	if defined(__ARM_ARCH_7A__)
#		define SROOK_ARM_ARCH_7A __ARM_ARCH_7A__
#	endif
#	if defined(__ARM_ARCH_7R__)
#		define SROOK_ARM_ARCH_7R __ARM_ARCH_7R__
#	endif
#	if defined(__ARM_ARCH_7M__)
#		define SROOK_ARM_ARCH_7M __ARM_ARCH_7M__
#	endif
#	if defined(SROOK_ARCH_ARM_THUMB_CHECK_MORE_COMPREHENSIVE)
#		if defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__) || defined(__ARM_ARCH_4__) || defined(__ARM_ARCH_4T__)
#			define SROOK_ARM_THUMB_IS_TRADITIONAL 1
#			define SROOK_THUMB2_COMPATIBLE 0
#		else
#			define SROOK_ARM_THUMB_IS_TRADITIONAL 0
#			define SROOK_THUMB2_COMPATIBLE 1
#		endif
#	else
#		if defined(SROOK_ARM_ARCH_4) || defined(SROOK_ARM_ARCH_4T)
#			define SROOK_ARM_THUMB_IS_TRADITIONAL 1
#			define SROOK_ARM_THUMB2_COMPATIBLE 0
#		else
#			define SROOK_ARM_THUMB_IS_TRADITIONAL 0
#			define SROOK_ARM_THUMB2_COMPATIBLE 1
#		endif
#	endif
#	if defined(__thumb__) && !defined(__thumb2__)
#		define SROOK_ARM_TARGET_IS_THUMB1 1
#		define SROOK_ARM_TARGET_IS_THUMB2 0
#	elif defined(__thumb__) && defined(__thumb2__)
#		define SROOK_ARM_TARGET_IS_THUMB1 0
#		define SROOK_ARM_TARGET_IS_THUMB2 1
#	endif
#else
#	define SROOK_ARCH_IS_ARM 0
#	define SROOK_TARGET_ARCH_ARM 0
#	define SROOK_ARM_ARCH_2 0
#	define SROOK_ARM_ARCH_3 0
#	define SROOK_ARM_ARCH_3M 0
#	define SROOK_ARM_ARCH_4 0
#	define SROOK_ARM_ARCH_5 0
#	define SROOK_ARM_ARCH_5E 0
#	define SROOK_ARM_ARCH_5T 0
#	define SROOK_ARM_ARCH_5TE 0
#	define SROOK_ARM_ARCH_5TEJ 0
#	define SROOK_ARM_ARCH_6 0
#	define SROOK_ARM_ARCH_6J 0
#	define SROOK_ARM_ARCH_6K 0
#	define SROOK_ARM_ARCH_6Z 0
#	define SROOK_ARM_ARCH_6ZK 0
#	define SROOK_ARM_ARCH_6T2 0
#	define SROOK_ARM_ARCH_7 0
#	define SROOK_ARM_ARCH_7A 0
#	define SROOK_ARM_ARCH_7R 0
#	define SROOK_ARM_ARCH_7M 0
#	define SROOK_ARM_THUMB_IS_TRADITIONAL 0
#	define SROOK_THUMB2_COMPATIBLE 0
#	define SROOK_ARM_TARGET_IS_THUMB1 0
#	define SROOK_ARM_TARGET_IS_THUMB2 0
#endif
#endif
