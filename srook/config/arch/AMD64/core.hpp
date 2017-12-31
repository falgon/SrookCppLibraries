// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ARCH_AMD64_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_AMD64_CORE_HPP
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#	define SROOK_ARCH_IS_AMD64 1
#else
#	define SROOK_ARCH_IS_AMD64 0
#endif
#endif
