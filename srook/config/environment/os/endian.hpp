// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ENV_ENDIAN_HPP
#define INCLUDED_SROOK_CONFIG_ENV_ENDIAN_HPP

#include <srook/config/environment/os/endian/linux/header.hpp>

#ifdef __LITTLE_ENDIAN__
#	if __LITTLE_ENDIAN__
#		define SROOK_LITTLE_ENDIAN 1
#		define SROOK_BIG_ENDIAN 0
#	endif
#endif

#if defined(__BIG_ENDIAN__)
#	if __BIG_ENDIAN__
#		define SROOK_BIG_ENDIAN 1
#		define SROOK_LITTLE_ENDIAN 0
#	endif
#endif

#if defined(__BYTE_ORDER__)
#	if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#		define SROOK_LITTLE_ENDIAN 1
#		define SROOK_BIG_ENDIAN 0
#	elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#		define SROOK_LITTLE_ENDIAN 0
#		define SROOK_BIG_ENDIAN 1
#	endif
#endif

#include <srook/config/environment/os/endian/FreeBSD/header.hpp>
#include <srook/config/environment/os/endian/NetBSD/header.hpp>
#include <srook/config/environment/os/endian/Win32/header.hpp>
#include <srook/config/environment/os/endian/sun/header.hpp>

#if !defined(SROOK_LITTLE_ENDIAN) || !defined(SROOK_BIG_ENDIAN)
#	include <endian.h>
#	if __BYTE_ORDER__ == __LITTLE_ENDIAN
#		define SROOK_LITTLE_ENDIAN 1
#		define SROOK_BIG_ENDIAN 0
#	elif
#		define SROOK_LITTLE_ENDIAN 0
#		define SROOK_BIG_ENDIAN 1
#	else
#		error unable to determine endian
#	endif
#endif

#endif
