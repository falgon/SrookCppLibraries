// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_NODISCARD_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_NODISCARD_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if SROOK_HAS_CPP_ATTRIBUTE_NODISCARD || (defined(_MSC_VER) && (_MSC_VER > 1911))
#    define SROOK_ATTRIBUTE_NODISCARD [[nodiscard]]
#elif (defined(__GNUC__) || defined(__clang__)) && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#    define SROOK_ATTRIBUTE_NODISCARD [[gnu::warn_unused_result]]
#elif (defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__)
#    define SROOK_ATTRIBUTE_NODISCARD __attribute__((__warn_unused_result__))
#elif defined(_MSC_VER) && (_MSC_VER >= 1700)
#    define SROOK_ATTRIBUTE_NODISCARD _Check_return_
#else
#    define SROOK_ATTRIBUTE_NODISCARD
#endif

#endif
