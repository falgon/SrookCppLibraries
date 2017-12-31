// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_BLACKFIN_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_BLACKFIN_HPP

#if defined(__bfin__) || defined(__BFIN__) || defined(bfin) || defined(BFIN)
#	define SROOK_ARCH_IS_BFIN 1
#else
#	define SROOK_ARCH_IS_BFIN 0
#endif

#endif
