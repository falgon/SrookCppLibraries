// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TEMPLETE_HIDDEN_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TEMPLETE_HIDDEN_HPP

#include <srook/config/user_config.hpp>

#if !defined(_WIN32) && !defined(__CYGWIN__) && !defined(SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS) && !defined(SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS)
#	if defined(__GNUC__)
#		if __GNUC__ >= 4 && __has_cpp_attribute(__type_visibility__)
#			define SROOK_ATTRIBUTE_TEMPLATE_VIS_HIDDEN __attribute__((__type_visibility__("hidden")))
#		else
#			define SROOK_ATTRIBUTE_TEMPLATE_VIS_HIDDEN __attribute__((__visibility__("hidden")))
#		endif
#	elif defined(__clang__)
#		if __has_cpp_attribute(__type_visibility__)
#			define SROOK_ATTRIBUTE_TEMPLATE_VIS_HIDDEN __attribute__((__type_visibility__("hidden")))
#		else
#			define SROOK_ATTRIBUTE_TEMPLATE_VIS_HIDDEN __attribute__((__visibility__("hidden")))
#		endif
#	endif
#endif

#ifndef SROOK_ATTRIBUTE_TEMPLATE_VIS_HIDDEN
#	define SROOK_ATTRIBUTE_TEMPLATE_VIS_HIDDEN
#endif

#endif
