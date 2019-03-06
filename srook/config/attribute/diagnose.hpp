// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_DIAGNOSE_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_DIAGNOSE_HPP

#include <srook/config/user_config.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>

#if __has_attribute(diagnose_if) &&\
   	SROOK_CONFIG_DIABLE_ADDITIONAL_DIAGNOSTICS
#	define SROOK_DIAGNOSE_WARNING(...)\
	__attribute__((diagnose_if(__VA_ARGS__, "warnig")))
#	define SROOK_DIAGNOSE_ERROR(...)\
	__attribute__((diagnose_if(__VA_ARGS__, "error")))
#else
#	define SROOK_DIAGNOSE_WARNING(...)
#	define SROOK_DIAGNOSE_ERROR(...)
#endif

#endif
