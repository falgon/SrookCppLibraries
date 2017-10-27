// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_DECLTYPE_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_DECLTYPE_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/compiler.hpp>

#if SROOK_CPP_DECLTYPE
#	define SROOK_DECLTYPE(T) decltype(T)
#elif defined(__clang__)
#	define SROOK_DECLTYPE(T) decltype(T)
#elif defined(_MSC_VER)
#	define SROOK_DECLTYPE(T) __typeof(T)
#elif defined(_GNUC_VER)
#	if _GNUC_VER >= 406
#		define SROOK_DECLTYPE(T) __decltype(T)
#	endif
#elif defined(__GNUC__) || SROOK_COMPILER_IS_ILE
#	define SROOK_DECLTYPE(T) __typeof__(T)
#endif


#endif
