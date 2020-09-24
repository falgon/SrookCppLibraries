// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ABI_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ABI_CORE_HPP

#include <srook/config/env.hpp>

#ifdef _LIBCPP_ABI_VERSION
#	define SROOK_ABI_VERSION _LIBCPP_ABI_VERSION
#else
#	define SROOK_ABI_VERSION 1
#endif

#if defined(SROOK_ABI_UNSTABLE) || SROOK_ABI_VERSION >= 2
#	

#endif
