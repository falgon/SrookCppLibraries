// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_CONSTEXPR_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_CONSTEXPR_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && !defined(SROOK_NO_CONSTTEXPR)
#    define SROOK_NO_CONSTEXPR
#    define SROOK_NO_CXX11_CONSTEXPR
#    define SROOK_NO_CXX14_CONSTEXPR
#endif

#if defined(SROOK_NO_CXX11_CONSTEXPR) || defined(SROOK_NO_CONSTEXPR)
#    define SROOK_CONSTEXPR
#    define SROOK_CONSTEXPR_OR_CONST const
#else
#    define SROOK_CONSTEXPR constexpr
#    define SROOK_CONSTEXPR_OR_CONST constexpr
#endif

#if defined(SROOK_NO_CXX14_CONSTEXPR)
#    define SROOK_CXX14_CONSTEXPR
#else
#    define SROOK_CXX14_CONSTEXPR constexpr
#endif

#endif
