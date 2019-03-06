// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_DETAIL_ENUM_VIS_DEFAULT_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_DETAIL_ENUM_VIS_DEFAULT_HPP

#include <srook/config/user_config.hpp> 

#ifndef SROOK_ATTRIBUTE_ENUM_VIS_DEFAULT
#	if !defined(SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS) && __has_cpp_attribute(__type_visibility__)
#		define SROOK_ATTRIBUTE_ENUM_VIS_DEFAULT __attribute__((__type_visibility__("default")))
#	elif !defined(SROOK_ATTRIBUTE_ENUM_VIS_DEFAULT)
#		define SROOK_ATTRIBUTE_ENUM_VIS_DEFAULT
#	endif
#endif

#endif
