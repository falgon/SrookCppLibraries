// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_SYSTEM390_CORE_HPP
#define INCLUDED_SROOK_CONFIG_SYSTEM390_CORE_HPP
#if defined(__s390__) || defined(__s390x__)
#	define SROOK_ARCH_IS_SYSTEM370 1
#else
#	define SROOK_ARCH_IS_SYSTEM370 0
#endif
#endif
