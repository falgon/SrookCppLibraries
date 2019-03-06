// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_MAYBE_UNUSED_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_MAYBE_UNUSED_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#if defined(__GNUC__)
#ifdef SROOK_ATTRIBUTE_UNUSED
#   undef SROOK_ATTRIBUTE_UNUSED
#endif
#define SROOK_ATTRIBUTE_UNUSED [[gnu::unused]]
#define SROOK_ATTRIBUTE_MAYBE_UNUSED SROOK_ATTRIBUTE_UNUSED
#else
#define SROOK_ATTRIBUTE_UNUSED [[maybe_unused]]
#define SROOK_ATTRIBUTE_MAYBE_UNUSED SROOK_ATTRIBUTE_UNUSED
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define SROOK_ATTRIBUTE_UNUSED __attribute__((unused))
#define SROOK_ATTRIBUTE_MAYBE_UNUSED SROOK_ATTRIBUTE_UNUSED
#else
#define SROOK_ATTRIBUTE_UNUSED
#define SROOK_ATTRIBUTE_MAYBE_UNUSED SROOK_ATTRIBUTE_UNUSED
#endif

#endif
