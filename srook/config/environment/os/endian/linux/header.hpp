// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_LINUX_LINUX_OS_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_LINUX_LINUX_OS_HPP

#ifdef __linux__
#	include <features.h>
#	ifndef __GLIBC_PREREQ
#		define SROOK_GLIBC_PREREQ(x, y) 0
#	endif
#endif

#endif
