// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ARCH_X86_64_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ARCH_X86_64_CORE_HPP
#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || defined(_M_X64)
#	define SROOK_ARCH_IS_X86_64 1
#else
#	define SROOK_ARCH_IS_X86_64 0
#endif
#endif
