// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_INLINE_VISIBILITY_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_INLINE_VISIBILITY_HPP

#include <srook/config/user_config.hpp>

#if !defined(_WIN32) && !defined(__CYGWIN__) && !defined(SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS) && !defined(SROOK_ATTRIBUTE_INLINE_VISIBILITY)
#	if defined(__GNUC__)
#		if __GNUC__ >= 4
#			define SROOK_ATTRIBUTE_INLINE_VISIBILITY __attribute__ ((__visibility__("hidden"), __always_inline__))
#		endif
#	elif defined(__clang__)
#		define SROOK_ATTRIBUTE_INLINE_VISIBILITY _LIBCPP_INLINE_VISIBILITY
#	endif
#endif

#ifndef SROOK_ATTRIBUTE_INLINE_VISIBILITY
#	define SROOK_ATTRIBUTE_INLINE_VISIBILITY
#endif

#endif
