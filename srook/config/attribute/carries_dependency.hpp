// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_CARRIES_DEPENDENCY_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_CARRIES_DEPENDENCY_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if (defined(__GCC__) || defined(__clang__)) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#define SROOK_CARRIES_DEPENDENCY [[carries_dependency]]
#else
#define SROOK_CARRIES_DEPENDENCY
#endif

#endif
