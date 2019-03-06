// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_RESTRICT_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_RESTRICT_HPP

#if !defined(SROOK_RESTRICT)
#if defined(_MSC_VER)
#	define SROOK_RESTRICT __restrict
#	if !defined(SROOK_NO_RESTRICT_REFERENCES) && (_MSC_FULL_VER < 190023026)
#		define SROOK_NO_RESTRICT_REFERENCES
#	endif
#elif defined(__GNUC__) && __GNUC__ > 3
#	define SROOK_RESTRICT __restrict__
#else
#	define SROOK_RESTRICT
#	if !defined(SROOK_NO_RESTRICT_REFERENCES)
#		define SROOK_NO_RESTRICT_REFERENCES
#	endif
#endif

#endif
#endif
