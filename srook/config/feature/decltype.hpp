// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_DECLTYPE_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_DECLTYPE_HPP

#include <srook/config/compiler.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if SROOK_CPP_DECLTYPE
#    define SROOK_DECLTYPE(...) decltype(__VA_ARGS__)
#elif defined(__clang__)
#    define SROOK_DECLTYPE(...) decltype(__VA_ARGS__)
#elif defined(_MSC_VER)
#    define SROOK_DECLTYPE(...) __typeof(__VA_ARGS__)
#elif defined(_GNUC_VER)
#    if _GNUC_VER >= 406
#        define SROOK_DECLTYPE(...) __decltype(__VA_ARGS__)
#    endif
#elif defined(__GNUC__) || SROOK_COMPILER_IS_ILE
#    define SROOK_DECLTYPE(...) __typeof__(__VA_ARGS__)
#endif

#endif
