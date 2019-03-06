// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_SYSTEM370_CORE_HPP
#define INCLUDED_SROOK_CONFIG_SYSTEM370_CORE_HPP
#if defined(__370__) || defined(__THW_370__)
#	define SROOK_ARCH_IS_SYSTEM370 1
#else
#	define SROOK_ARCH_IS_SYSTEM370 0
#endif
#endif
