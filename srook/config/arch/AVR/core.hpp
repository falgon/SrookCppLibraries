// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_COMPILER_AVR_CORE_HPP
#define INCLUDED_SROOK_CONFIG_COMPILER_AVR_CORE_HPP

#if defined(__AVR) && defined(__AVR__)
#	define SROOK_ARCH_IS_AVR 1
#else
#	define SROOK_ARCH_IS_AVR 0
#endif

#endif
