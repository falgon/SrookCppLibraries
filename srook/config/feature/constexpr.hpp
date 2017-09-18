// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_CONSTEXPR_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_CONSTEXPR_HPP

#if defined(SROOK_NO_CXX11) && !defined(SROOK_NO_CONSTTEXPR)
#	if defined(SROOK_NO_CXX11_CONSTEXPR) && !defined(SROOK_NO_CONSTTEXPR)
#		define SROOK_NO_CONSTEXPR
#	endif
#endif


#if defined(SROOK_NO_CXX11_CONSTEXPR)
#	define SROOK_CONSTEXPR
#	define SROOK_CONSTEXPR_OR_CONST const
#else
#	define SROOK_CONSTEXPR constexpr
#	define SROOK_CONSTEXPR_OR_CONST constexpr
#endif

#if defined(SROOK_NO_CXX14_CONSTEXPR)
#		define SROOK_CXX14_CONSTEXPR
#else
#	define SROOK_CXX14_CONSTEXPR constexpr
#endif

#endif
