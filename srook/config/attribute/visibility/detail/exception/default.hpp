// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_DETAIL_EXCEPTION_DEFAULT_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_DETAIL_EXCEPTION_DEFAULT_HPP

#include <srook/config/user_config.hpp>

#ifndef SROOK_ATTRIBUTE_EXCEPTION_ABI_DEFAULT
#	ifndef SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS
#		define SROOK_ATTRIBUTE_EXCEPTION_ABI_DEFAULT __attribute__((__visibility__("default")))
#	elif !defined(SROOK_ATTRIBUTE_EXCEPTION_ABI_DEFAULT)
#		define SROOK_ATTRIBUTE_EXCEPTION_ABI_DEFAULT
#	endif
#endif

#endif
