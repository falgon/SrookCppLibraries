// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_ALIGNED_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_ALIGNED_HPP

#include <srook/config/arch.hpp>
#include <srook/config/compiler.hpp>
#include <srook/config/cpp_predefined.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#	define SROOK_STD_ALIGNED alignas
#endif

#if defined(__GNUC__) || defined(__clang__)
#	define SROOK_ATTRIBUTE_ALIGNED __attribute__((__aligned__))
#	define SROOK_ATTRIBUTE_ALIGNED_X(x) __attribute__((__aligned__((x))))
#elif SROOK_ARCH_IS_ARM
#	define SROOK_ATTRIBUTE_ALIGNED __attribute__((aligned))
#	define SROOK_ATTRIBUTE_ALIGNED_X(x) __attribute__((aligned((x))))
#elif defined(_MSC_VER)
#	define SROOK_ATTRIBUTE_ALIGNED __declspec((align))
#	define SROOK_ATTRIBUTE_ALIGNED_X(x) __declspec((align((x))))
#elif SROOK_COMPILER_IS_ILE
#	define SROOK_ATTRIBUTE_ALIGNED __align
#	define SROOK_ATTRIBUTE_ALIGNED_X(x) __align(x)
#endif

#endif
