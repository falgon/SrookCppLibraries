// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_NO_RETURN_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_NO_RETURN_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if defined(_MSC_VER)
#define SROOK_NORETURN __declspec(noreturn)
#elif defined(__GNUC__)
#define SROOK_NORETURN __attribute__((__noreturn__))
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11
#define SROOK_NORETURN [[noreturn]]
#else
#define SROOK_NORETURN
#endif

#endif
