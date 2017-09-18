// Copyright (C) 2017 roki

#ifndef INCLUDED_SROOK_CONFIG_COMPILER_EXTENTION_LONGLONG_TYPE_HPP
#if !defined(SROOK_HAS_LONG_LONG) && !defind(SROOK_NO_LONG_LONG) && !defined(SROOK_MSVC) && !defined(__BORLANDC__)
#	include<limits.h>
#	if (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#		define SROOK_HAS_LONG_LONG
#	else
#		define SROOK_NO_LONG_LONG
#endif

#if defined(SROROK_HAS_LONG_LONG) && defined(__cplusplus)
namespace srook{
#ifdef __GNUC__
	__extention__ typedef long long long_long_type;
	__extention__ typedef unsigned long long ulong_long_type;
#else
	typedef long long long_long_type;
	typedef unsigned long long ulong_long_type;
#endif
} // namespace srook

#endif
#endif

