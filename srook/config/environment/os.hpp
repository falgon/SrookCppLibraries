// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_HPP

#include <srook/config/environment/os/endian.hpp>
#include <srook/config/environment/os/thread_api.hpp>
#include <srook/config/environment/os/filesystem.hpp>
#include <srook/config/environment/os/stdio.hpp>
#include <srook/config/environment/os/apple.hpp>

#if defined(__clang__)
#	define SROOK_HAS_BUILTIN_OPERATOR_NEW !defined(_LIBCPP_HAS_NO_BUILTIN_OPERATOR_NEW_DELETE)
#elif defined(__has_builtin)
#	if !__has_builtin(__builtin_operator_new) || !__has_builtin(__builtin_operator_delete)
#		define SROOK_HAS_BUILTIN_OPERATOR_NEW 0
#	else
#		define SROOK_HAS_BUILTIN_OPERATOR_NEW 1
#	endif
#else
#	define SROOK_HAS_BUILTIN_OPERATOR_NEW 0
#endif

#endif
