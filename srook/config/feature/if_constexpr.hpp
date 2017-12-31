// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_IF_CONSTEXPR_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_IF_CONSTEXPR_HPP

#include <srook/config/cpp_predefined.hpp>

#if __cpp_if_constexpr //SROOK_CPP_IF_CONSTEXPR
#    define SROOK_IF_CONSTEXPR \
        if                     \
        constexpr
#else
#    define SROOK_IF_CONSTEXPR if
#endif

#endif
