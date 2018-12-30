// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TEMPLETE_DEFAULT_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TEMPLETE_DEFAULT_HPP

#include <srook/config/user_config.hpp>

#if !defined(_WIN32) && !defined(__CYGWIN__) && !defined(SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS) && !defined(SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT)
#	if defined(__GNUC__)
#		if __GNUC__ >= 4 && __has_cpp_attribute(__type_visibility__)
#			define SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT __attribute__((__type_visibility__("default")))
#		else
#			define SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT __attribute__((__visibility__("default")))
#		endif
#	elif defined(__clang__)
#			define SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT _LIBCPP_TEMPLATE_VIS
#	endif
#endif

#ifndef SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT
#	define SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT
#endif

#endif
