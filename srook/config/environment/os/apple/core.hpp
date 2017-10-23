// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ENVIRONMENT_OS_APPLE_CORE_HPP
#define INCLUDED_SROOK_CONFIG_ENVIRONMENT_OS_APPLE_CORE_HPP

#ifdef __clang__
#	ifdef _LIBCPP_USE_AVAILABILITY_APPLE
#		define SROOK_APPLE 1
#	else
#		define SROOK_APPLE 0
#	endif
#endif

#if defined(__APPLE__) && defined(__has_feature)
#	if __has_feature(attribute_availability_with_strict) &&\
	__has_feature(attribute_availability_in_templates)
#		define SROOK_APPLE 1
#	else
#		define SROOK_APPLE 0
#	endif
#else
#	define SROOK_APPLE 0
#endif

#endif
