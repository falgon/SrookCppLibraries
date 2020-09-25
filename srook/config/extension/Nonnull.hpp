// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_EXTENSION_NONNULL_HPP
#define INCLUDED_SROOK_CONFIG_EXTENSION_NONNULL_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if defined(__clang__)
#	if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#		define SROOK_NONNULL [[gnu::nonnull]]
#		define SROOK_ATTRIBUTE_NONNULL SROOK_NONNULL
#	else
#		define SROOK_NONNULL _Nonnull
#		define SROOK_ATTRIBUTE_NONNULL SROOK_NONNULL
#	endif
#elif defined(__GNUC__)
#	define SROOK_NONNULL __attribute__((nonnull))
#	define SROOK_ATTRIBUTE_NONNULL SROOK_NONNULL
#else
#	define SROOK_NONNULL
#	define SROOK_ATTRIBUTE_NONNULL SROOK_NONNULL
#endif

#endif
