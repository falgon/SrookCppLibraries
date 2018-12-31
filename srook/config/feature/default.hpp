// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_DEFAULT_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_DEFAULT_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS
#    define SROOK_DEFAULT = default;
#else
#    define SROOK_DEFAULT \
        {                 \
        }
#endif

#endif
