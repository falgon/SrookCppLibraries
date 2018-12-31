// Copyright (C) 2011-2019 Roki. Distributed under the MIT License

#ifndef INCLUDED_SROOK_CONFIG_COMPILER_EXTENTION_LONGLONG_TYPE_HPP
#define INCLUDED_SROOK_CONFIG_COMPILER_EXTENTION_LONGLONG_TYPE_HPP

#include <srook/config/environment/os.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>

#if !defined(SROOK_HAS_LONG_LONG) && !defined(SROOK_NO_LONG_LONG) && !defined(SROOK_MSVC) && !defined(__BORLANDC__)
#	include <limits.h>
#	if (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#		define SROOK_HAS_LONG_LONG
#	else
#		define SROOK_NO_LONG_LONG
#	endif
#endif

#if defined(SROOK_HAS_LONG_LONG) && defined(SROOK_CPLUSPLUS)
namespace srook{
#ifdef __GNUC__
	__extension__ typedef long long long_long_type;
	__extension__ typedef unsigned long long ulong_long_type;
#else
	typedef long long long_long_type;
	typedef unsigned long long ulong_long_type;
#endif
} // namespace srook

#endif
#endif
