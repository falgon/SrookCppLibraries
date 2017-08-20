// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_MAYBE_UNUSED_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_MAYBE_UNUSED_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#if defined(__GNUC__)
#define SROOK_ATTRIBUTE_UNUSED [[gnu::unused]]
#else
#define SROOK_ATTRIBUTE_UNUSED [[maybe_unused]]
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define SROOK_ATTRIBUTE_UNUSED __attribute__((unused))
#else
#define SROOK_ATTRIBUTE_UNUSED
#endif

#endif
