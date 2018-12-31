// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_CONSTEXPR_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_CONSTEXPR_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT || defined(SROOK_NO_CONSTEXPR)
#   define SROOK_NO_CONSTEXPR
#   define SROOK_NO_CXX11_CONSTEXPR
#   define SROOK_NO_CXX14_CONSTEXPR
#   define SROOK_NO_CXX17_CONSTEXPR
#endif

#if !defined(SROOK_NO_CONSTEXPR) && !defined(SROOK_NO_CXX14_CONSTEXPR) && (SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT)
#   define SROOK_NO_CXX14_CONSTEXPR
#endif

#if !defined(SROOK_NO_CONSTEXPR) && !defined(SROOK_NO_CXX17_CONSTEXPR) && (SROOK_CPLUSPLUS < SROOK_CPLUSPLUS17_CONSTANT)
#   define SROOK_NO_CXX17_CONSTEXPR
#endif

#ifdef SROOK_NO_CONSTEXPR
#   define SROOK_CONSTEXPR
#   define SROOK_CONSTEXPR_OR_CONST const
#   define SROOK_CXX14_CONSTEXPR
#   define SROOK_CXX17_CONSTEXPR
#else
#   define SROOK_CONSTEXPR constexpr
#   define SROOK_CONSTEXPR_OR_CONST constexpr
#   ifndef SROOK_NO_CXX14_CONSTEXPR
#       define SROOK_CXX14_CONSTEXPR constexpr
#   else
#       define SROOK_CXX14_CONSTEXPR
#   endif
#   ifndef SROOK_NO_CXX17_CONSTEXPR
#       define SROOK_CXX17_CONSTEXPR constexpr
#   else
#       define SROOK_CXX17_CONSTEXPR
#   endif
#endif

#endif
