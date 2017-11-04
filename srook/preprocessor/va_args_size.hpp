// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_PREPROCESSOR_VA_ARGS_SIZE_HPP
#define INCLUDED_SROOK_PREPROCESSOR_VA_ARGS_SIZE_HPP

#include <srook/config/attribute/maybe_unused.hpp>
#include <srook/config/cpp_predefined.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_HAS_INCLUDE(<tuple>)
#    include <tuple>
#    define SROOK_PP_VA_ARGS_SIZE(...) \
        (SROOK_ATTRIBUTE_UNUSED std::tuple_size<decltype(std::tie(__VA_ARGS__))>::value)
#else
#    define SROOK_PP_VA_ARGS_SIZE(...) \
        (SROOK_ATTRIBUTE_UNUSED(sizeof((char[]){__VA_ARGS__}) / sizeof(char)))
#endif

#endif
