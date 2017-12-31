// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_TMS_320_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_TMS_320_HPP
#if defined(_TMS320C2XX) || defined(__TMS320C2000__) || defined(_TMS320C5X) || defined(__TMS320C55X__) || defined(_TMS320C6X) || defined(__TMS320C6X__)
#	define SROOK_ARCH_IS_TMS320 1
#	if defined(_TMS320C2XX)
#		define SROOK_TMS320C2XX _TMS320C2XX
#	elif defined(__TMS320C2000__)
#		define SROOK_TMS320C2XX __TMS320C2000__
#	else
#		define SROOK_TMS320C2XX 0
#	endif
#	if defined(_TMS320C5X)
#		define SROOK_TMS320C5X _TMS320C5X
#	elif defined(__TMS320C55X__)
#		define SROOK_TMS320C55X __TMS320C55X__
#	else
#		define SROOK_TMS320C55X 0
#	endif
#	if defined(_TMS320C6X)
#		define SROOK_TMS320C6X _TMS320C6X
#	elif defined(__TMS320C6X__)
#		define SROOK_TMS320C6X __TMS320C6X__
#	else
#		define SROOK_TMS320C6X 0
#	endif
#else
#	define SROOK_ARCH_IS_TMS320 0
#	define SROOK_TMS320C2XX 0
#	define SROOK_TMS320C55X 0
#	define SROOK_TMS320C6X 0
#endif
#endif
