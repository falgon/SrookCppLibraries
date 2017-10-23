// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_DEPRECATED_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_DEPRECATED_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if defined(__GNUC__) || defined(__clang__)
#	define SROOK_DEPRECATED __attribute__((deprecated))
#	define SROOK_DEPRECATED_MESSAGE(mes) __attribute__((deprecated(mes)))
#elif defined(_MSC_VER)
#	define SROOK_DEPRECATED __declspec(deprecated)
#	define SROOK_DEPRECATED_MESSAGE(mes) __declspec(deprecated(mes))
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
#	define SROOK_DEPRECATED [[deprecated]]
#	define SROOK_DEPRECATED_MESSAGE(mes) [[deprecated(mes)]]
#else
#	define SROOK_DEPRECATED
#	define SROOK_DEPRECATED_MESSAGE(...)
#endif

#endif
