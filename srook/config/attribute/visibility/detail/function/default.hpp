// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_FUNCTION_DEFAULT_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_FUNCTION_DEFAULT_HPP

#include <srook/config/user_config.hpp>

#if !defined(_WIN32) && !defined(__CYGWIN__) && !defined(SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS) && !defined(SROOK_ATTRIBUTE_FUNCTION_VIS_DEFAULT)
#	if defined(__GNUC__)
#		if __GNUC__ >= 4
#			define SROOK_ATTRIBUTE_FUNCTION_VIS_DEFAULT __attribute__((__visibility__("default")))
#		endif
#	elif defined(__clang__) && !defined(SROOK_ATTRIBUTE_FUNCTION_VIS_DEFAULT)
#		define SROOK_ATTRIBUTE_FUNCTION_VIS_DEFAULT _LIBCPP_FUNC_VIS
#	endif
#endif

#ifndef SROOK_ATTRIBUTE_FUNCTION_VIS_DEFAULT
#	define SROOK_ATTRIBUTE_FUNCTION_VIS_DEFAULT
#endif

#endif
