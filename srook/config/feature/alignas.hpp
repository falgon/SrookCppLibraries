// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_ALIGNNAS_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_ALIGNNAS_HPP
#if !defined(SROOK_ALIGNMENT)
#	if !defined(SROOK_NO_CXX11_ALIGNAS)
#		define SROOK_ALIGNMENT(x) alignas(x)
#	elif defined(_MSC_VER)
#		define SROOK_ALIGNMENT(x) __declspec(align(x))
#	elif defined(__GNUC__)
#		define SROOK_ALIGNMENT(x) __attribute__((__aligned__(x)))
#	else
#		define SROOK_NO_ALIGNMENT
#		define SROOK_ALIGNMENT(x)
#	endif
#endif
#endif
