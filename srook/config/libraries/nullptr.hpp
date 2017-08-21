// Copyright 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_LIBRARIES_NULLPTR_HPP
#define INCLUDED_SROOK_CONFIG_LIBRARIES_NULLPTR_HPP

#include<srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include<srook/config/cpp_predefined/macro_names.hpp>
#include<srook/config/cpp_predefined/feature_testing.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#	define SROOK_NULLPTR nullptr
#	define SROOK_NULLPTR_T std::nullptr_t
#else
#	include<srook/config/nullptr.hpp>
#	define SROOK_NULLPTR srook::nullptr
#	define SROOK_NULLPTR_T srook::nullptr_t
#endif

#endif
