// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_EXPLICIT_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_EXPLICIT_HPP

#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>

#if defined(__clang__) && defined(_LIBCPP_EXPLICIT)
#	define SROOK_EXPLICIT _LIBCPP_EXPLICIT
#elif defined(__GNUC__) && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#	define SROOK_EXPLICIT explicit
#elif defined(_MSC_VER)
#	if _MSC_VER > 1700
#		define SROOK_EXPLICIT explicit
#	endif
#else
#	define SROOK_EXPLICIT
#endif

#endif
