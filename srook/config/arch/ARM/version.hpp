// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
// Reference: http://infocenter.arm.com/help/topic/com.arm.doc.dui0376d/DUI0376D_compiler_reference.pdf
#ifndef INCLUDED_SROOK_CONFIG_ARCH_ARM_VERSION_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_ARM_VERSION_HPP
#include <srook/config/arch/ARM/arm64.hpp>
#include <srook/config/arch/ARM/core.hpp>

#if SROOK_ARCH_IS_ARM
#	if SROOK_ARCH_IS_ARM64
#		define SROOK_ARCH_ARM_VERSION 8.0
#		if defined(__TARGET_ARCH_THUMB)
#			define SROOK_ARCH_ARM_THUMB_VALUE __TARGET_ARCH_THUMB
#		else
#			define SROOK_ARCH_ARM_THUMB_VALUE 0.0
#		endif
#	elif SROOK_TARGET_ARCH_ARM && defined(__TARGET_ARCH_THUMB)
#		define SROOK_ARCH_ARM_VERSION SROOK_TARGET_ARCH_ARM
#		if defined(__TARGET_ARCH_THUMB)
#			define SROOK_ARCH_ARM_THUMB_VALUE __TARGET_ARCH_THUMB
#		else
#			define SROOK_ARCH_ARM_THUMN_VALUE 0.0
#		endif
#	elif defined(_M_ARM)
#		define SROOK_ARCH_ARM_VERSION _M_ARM
#		if defined(__TARGET_ARCH_THUMB)
#			define SROOK_ARCH_ARM_THUMB_VALUE __TARGET_ARCH_THUMB
#		else
#			define SROOK_ARCH_ARM_THUMB_VALUE 0.0
#		endif
#	endif
#else
#	define SROOK_ARCH_ARM_VERSION 0.0
#	define SROOK_ARCH_ARM_THUMB_VALUE 0.0
#endif

#endif
