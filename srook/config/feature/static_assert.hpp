// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_STATIC_ASSERT_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_STATIC_ASSERT_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/preprocessor/concat.hpp>

#if SROOK_CPP_STATIC_ASSERT && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#    define SROOK_STATIC_ASSERT(x, y) static_assert(x, y)
#    if SROOK_CPP_STATIC_ASSERT > 201400
#        define SROOK_ST_ASSERT(...) static_assert(__VA_ARGS__)
#    else
#        define SROOK_ST_ASSERT(...) SROOK_STATIC_ASSERT(__VA_ARGS__, #__VA_ARGS__)
#    endif
#elif defined(__clang__) && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#    define SROOK_STATIC_ASSERT(x, y) static_assert(x, y)
#    define SROOK_ST_ASSERT(...) SROOK_STATIC_ASSERT(__VA_ARGS__, #__VA_ARGS__)
#elif defined(__has_extension)
#    if __has_extension(c_static_assert)
#        define SROOK_STATIC_ASSERT(x, y) _Static_assert(x, y)
#        define SROOK_ST_ASSERT(...) SROOK_STATIC_ASSERT(__VA_ARGS__, #__VA_ARGS__)
#    endif
#else

extern "C++" {

template <bool>
struct static_assert_test;
template <>
struct static_assert_test<true> {};
template <unsigned>
struct static_assert_check {};

}

#    define SROOK_STATIC_ASSERT(x, y)                                \
        typedef static_assert_check<sizeof(static_assert_test<(x)>)> \
            SROOK_CONCAT(__t, SROOK_LINE)
#    define SROOK_ST_ASSERT(...) SROOK_STATIC_ASSERT(__VA_ARGS__, #__VA_ARGS__)
#endif

#endif
