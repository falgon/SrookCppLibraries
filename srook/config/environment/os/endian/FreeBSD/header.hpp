// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_BSD_HEADER_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_BSD_HEADER_HPP

#ifdef __FreeBSD__
#	include <sys/endian.h>
#	if _BYTE_ORDER == _LITTLE_ENDIAN
#		define SROOK_LITTLE_ENDIAN 1
#		define SROOK_BIG_ENDIAN 0
#	else
#		define SROOK_LITTLE_ENDIAN 0
#		define SROOK_BIG_ENDIAN 1
#	endif
#	ifndef __LONG_LONG_SUPPORTED
#		define SROOK_HAS_LONG_LONG 0
#	else
#		define SROOK_HAS_LONG_LONG 1
#	endif
#endif

#endif
