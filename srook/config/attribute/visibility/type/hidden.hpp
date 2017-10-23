// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TYPE_HIDDEN_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TYPE_HIDDEN_HPP

#if !defined(_WIN32) && !defined(__CYGWIN__)
#	if defined(__GNUC__)
#		if __GNUC__ >= 4
#			define SROOK_ATTRIBUTE_TYPE_VIS_HIDDEN __attribute__((__visibility__("hidden")))
#		endif
#	elif defined(__clang__)
#		define SROOK_ATTRIBUTE_TYPE_VIS_HIDDEN __attribute__((__visibility__("hidden")))
#	endif
#endif

#ifndef SROOK_ATTRIBUTE_TYPE_VIS_HIDDEN
#	define SROOK_ATTRIBUTE_TYPE_VIS_HIDDEN
#endif

#endif
