// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TEMPLETE_HIDDEN_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_TEMPLETE_HIDDEN_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>

#if !defined(_WIN32) && !defined(__CYGWIN__)
#	if defined(__GNUC__)
#		if __GNUC__ >= 4 && SROOK_HAS_CPP_ATTRIBUTE(__type_visibility__)
#			define SROOK_ATTRIBUTE_TEMPLATE_VIS_HIDDEN __attribute__((__type_visibility__("hidden")))
#		else
#			define SROOK_ATTRIBUTE_TEMPLATE_VIS_HIDDEN __attribute__((__visibility__("hidden")))
#		endif
#	elif defined(__clang__)
#		if SROOK_HAS_CPP_ATTRIBUTE(__type_visibility__)
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
