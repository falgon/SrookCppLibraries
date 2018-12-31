// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_FALLTHROUGH_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_FALLTHROUGH_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT) && SROOK_HAS_CPP_ATTRIBUTE_FALLTHROUGH
#	define SROOK_ATTRIBUTE_FALLTHROUGH [[fallthrough]]
#elif defined(__clang__)
#	define SROOK_ATTRIBUTE_FALLTHROUGH [[clang::fallthrough]]
#elif defined(__GNUC__)
#	define SROOK_ATTRIBUTE_FALLTHROUGH __attribute__((fallthrough))
#else
#	define SROOK_ATTRIBUTE_FALLTHROUGH ((void)0)
#endif

#endif
