// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_NODISCARD_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_NODISCARD_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if ((SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT) && SROOK_HAS_CPP_ATTRIBUTE_NODISCARD) || (defined(__clang__) && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT))
#define SROOK_ATTRIBUTE_NODISCARD [[nodiscard]]
#elif defined(__GNUC__)
#define SROOK_ATTRIBUTE_NODISCARD [[gnu::warn_unused_result]]
#endif

#endif
