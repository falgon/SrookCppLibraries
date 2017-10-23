// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_STDIO_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_STDIO_HPP

#ifndef __CloudABI__
#	define SROOK_HAS_STDIN 1
#	define SROOK_HAS_STDOUT 1
#else
#	define SROOK_HAS_STDIN 0
#	define SROOK_HAS_STDOUT 0
#endif

#endif
