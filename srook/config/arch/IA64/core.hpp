// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_IA64_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_IA64_CORE_HPP

#if defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64) || defined(__itanium__)
#	define SROOK_ARCH_IS_IA64 1
#else
#	define SROOK_ARCH_IS_IA64 0
#endif

#endif
