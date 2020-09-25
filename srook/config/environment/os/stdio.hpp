// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
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
