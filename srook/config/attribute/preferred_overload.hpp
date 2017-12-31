// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_PREFERRED_OVERLOAD_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_PREFERRED_OVERLOAD_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>

#ifndef SROOK_PREFERRED_OVERLOAD
#	if defined(__clang__) && defined(_LIBCPP_PREFERRED_OVERLOAD)
#		define SROOK_PREFERRED_OVERLOAD _LIBCPP_PREFERRED_OVERLOAD
#	elif SROOK_HAS_CPP_ATTRIBUTE(__enable_if__)
#		define SROOK_PREFERRED_OVERLOAD __attribute__((__enable_if__(true, "")))
#	else
#		define SROOK_PREFERRED_OVERLOAD
#	endif
#endif

#endif
