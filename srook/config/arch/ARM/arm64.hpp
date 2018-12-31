// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
// Reference: http://infocenter.arm.com/help/topic/com.arm.doc.dui0376d/DUI0376D_compiler_reference.pdf

#ifndef INCLUDED_SROOK_CONFIG_ARCH_ARM_ARM64_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_ARM_ARM64_HPP

#if defined(__aarch64__) || defined(_M_ARM64)
#	define SROOK_ARCH_IS_ARM64 1
#else
#	define SROOK_ARCH_IS_ARM64 0
#endif

#endif
