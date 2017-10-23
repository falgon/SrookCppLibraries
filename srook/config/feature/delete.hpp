// Copyright (C) 2017 roki
#ifndef INCLUDE_SROOK_CONFIG_FEATURE_DELETE_HPP
#define INCLUDE_SROOK_CONFIG_FEATURE_DELETE_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS
#	define SROOK_EQ_DELETE = delete;
#else
#	define SROOK_EQ_DELETE ;
#endif

#endif
