// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_DECALPHA_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_DECALPHA_CORE_HPP

#if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
#	define SROOK_ARCH_IS_DECALPHA 1
#	if defined(__alpha_ev4__)
#		define SROOK_ALPHA_EV4 __alpha_ev4__
#	else
#		define SROOK_ALPHA_EV4 0
#	endif
#	if defined(__alpha_ev5__)
#		define SROOK_ALPHA_EV5 __alpha_ev5__
#	else
#		define SROOK_ALPHA_EV5 0
#	endif
#	if defined(__alpha_ev6__)
#		define SROOK_ALPHA_EV6 __alpha_ev6__
#	else
#		define SROOK_ALPHA_EV6 0
#	endif
#else
#	define SROOK_ARCH_IS_DECALPHA 0
#	define SROOK_ALPHA_EV4 0
#	define SROOK_ALPHA_EV5 0
#	define SROOK_ALPHA_EV6 0
#endif

#endif
