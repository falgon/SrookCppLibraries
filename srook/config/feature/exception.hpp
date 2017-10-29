// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_EXCEPTION_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_EXCEPTION_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>

#if SROOK_CPP_EXCEPTIONS
#	define SROOK_TRY try
#	define SROOK_CATCH(x) catch(x)
#	define SROOK_THROW throw
#else
#	define SROOK_TRY if (true)
#	define SROOK_CATCH(x) if (false)
#	define SROOK_THROW
#endif

#endif
