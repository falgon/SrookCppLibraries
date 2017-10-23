// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TEMPLETE_DEFAULT_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TEMPLETE_DEFAULT_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>

#if !defined(_WIN32) && !defined(__CYGWIN__)
#	if defined(__GNUC__)
#		if __GNUC__ >= 4 && SROOK_HAS_CPP_ATTRIBUTE(__type_visibility__)
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
