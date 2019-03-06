// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_ZERO_INIT_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_ZERO_INIT_HPP

#include <srook/config/arch.hpp>

#if SROOK_ARCH_IS_ARM
#	define SROOK_ATTRIBUTE_ZERO_INIT(x) __attribute__((section(x), zero_init))
#	define SROOK_ATTRIBUTE_SECTION_BSS __attribute__((zero_init))
#else
#	define SROOK_ATTRIBUTE_ZERO_INIT(x)
#	define SROOK_ATTRIBUTE_SECTION_BSS
#endif

#endif
