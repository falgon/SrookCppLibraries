// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_FINAL_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_FINAL_HPP

#include <srook/config/cpp_predefined.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    define SROOK_FINAL final
#else
#    define SROOK_FINAL
#endif

#endif
