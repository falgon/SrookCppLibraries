// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_ENDIAN_SUN_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_ENDIAN_SUN_HPP

#if __sun__
#	include <sys/isa_defs.h>
#   if !defined(SROOK_LITTLE_ENDIAN)
#		define SROOK_LITTLE_ENDIAN 1
#   endif
#	if !defined(SROOK_BIG_ENDIAN)
#		define SROOK_BIG_ENDIAN 0
#	endif
#else
#	if !defined(SROOK_LITTLE_ENDIAN)
#		define SROOK_LITTLE_ENDIAN 0
#	endif
#	if !defined(SROOK_BIG_ENDIAN)
#		define SROOK_BIG_ENDIAN 1
#	endif
#endif

#endif
