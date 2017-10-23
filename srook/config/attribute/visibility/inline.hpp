// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_INLINE_VISIBILITY_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_INLINE_VISIBILITY_HPP

#if !defined(_WIN32) && !defined(__CYGWIN__)
#	if defined(__GNUC__)
#		if __GNUC__ >= 4
#			define SROOK_ATTRIBUTE_INLINE_VISIBILITY __attribute__ ((__visibility__("hidden"), __always_inline__))
#		endif
#	elif defined(__clang__)
#		define SROOK_ATTRIBUTE_INLINE_VISIBILITY _LIBCPP_INLINE_VISIBILITY
#	endif
#endif

#ifndef SROOK_ATTRIBUTE_TYPE_VIS_HIDDEN
#	define SROOK_ATTRIBUTE_INLINE_VISIBILITY
#endif

#endif
