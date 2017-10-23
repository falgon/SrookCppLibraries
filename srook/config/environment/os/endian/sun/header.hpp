// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_ENDIAN_SUN_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_ENDIAN_SUN_HPP

#if __sun__
#	include <sys/isa_defs.h>
#	define SROOK_LITTLE_ENDIAN 1
#	define SROOK_BIG_ENDIAN 0
#else
#	define SROOK_LITTLE_ENDIAN 0
#	define SROOK_BIG_ENDIAN 1
#endif

#endif
