// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_RS6000_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_RS6000_CORE_HPP

#if defined(__THW_RS6000) || defined(_IBMR2) || defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2)
#	define SROOK_ARCH_IS_RS6000 1
#else
#	define SROOK_ARCH_IS_RS6000 0
#endif

#endif
