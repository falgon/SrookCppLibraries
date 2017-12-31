// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TYPE_HIDDEN_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TYPE_HIDDEN_HPP

#include <srook/config/user_config.hpp>

#if !defined(_WIN32) && !defined(__CYGWIN__) && !defined(SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS) && !defined(SROOK_ATTRIBUTE_TYPE_VIS_HIDDEN)
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
