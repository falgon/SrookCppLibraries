// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_CONVEX_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_CONVEX_CORE_HPP

#if defined(__convex__) 
#	define SROOK_ARCH_IS_CONVEX 1
#	if defined(__convex_c1__)
#		define SROOK_CONVEX_C1 __convex_c1__
#	else
#		define SROOK_CONVEX_C1 0
#	endif
#	if defined(__convex_c2__)
#		define SROOK_CONVEX_C2 __convex_c2__
#	else
#		define SROOK_CONVEX_C2 0
#	endif
#	if defined(__convex_c32__)
#		define SROOK_CONVEX_C32 __convex_c32__
#	else
#		define SROOK_CONVEX_C32 0
#	endif
#	if defiend(__convex_c34__)
#		define SROOK_CONVEX_C34 __convex_c34__
#	else
#		define SROOK_CONVEX_C34 0
#	endif
#	if defined(__convex_c38__)
#		define SROOK_CONVEX_C38 __convex_c38__
#	else
#		define SROOK_CONVEX_C38 0
#	endif
#else
#	define SROOK_ARCH_IS_CONVEX 0
#	define SROOK_CONVEX_C1 0
#	define SROOK_CONVEX_C2 0
#	define SROOK_CONVEX_C32 0
#	define SROOK_CONVEX_C34 0
#	define SROOK_CONVEX_C38 0
#endif

#endif
