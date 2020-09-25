// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_PREPROCESSOR_VA_COUNT_HPP
#define INCLUDED_SROOK_PREPROCESSOR_VA_COUNT_HPP

#include <srook/preprocessor/not.hpp>

#if defined(_MSC_VER)
#    define SROOK_PP_DUMMY_VA(...) dummy, __VA_ARGS__
#else
#    define SROOK_PP_DUMMY_VA(...) dummy, __VA_ARGS__
#endif

#define SROOK_PP_VA_COUNT(...) SROOK_PP_INDIRECT(SROOK_PP_VA_COUNT_INTERNAL_0((SROOK_PP_DUMMY_VA(__VA_ARGS__), \
                                                                               63, 62, 61, 60, 59, 58, 57, 56, \
                                                                               55, 54, 53, 52, 51, 50, 49, 48, \
                                                                               47, 46, 45, 44, 43, 42, 41, 40, \
                                                                               39, 38, 37, 36, 35, 34, 33, 32, \
                                                                               31, 30, 29, 28, 27, 26, 25, 24, \
                                                                               23, 22, 21, 20, 19, 18, 17, 16, \
                                                                               15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)))

#define SROOK_PP_VA_COUNT_INTERNAL_0(X) SROOK_PP_INDIRECT(SROOK_PP_VA_COUNT_INTERNAL_1 X)
#define SROOK_PP_VA_COUNT_INTERNAL_1(       \
    _01, _02, _03, _04, _05, _06, _07, _08, \
    _09, _10, _11, _12, _13, _14, _15, _16, \
    _17, _18, _19, _20, _21, _22, _23, _24, \
    _25, _26, _27, _28, _29, _30, _31, _32, \
    _33, _34, _35, _36, _37, _38, _39, _40, \
    _41, _42, _43, _44, _45, _46, _47, _48, \
    _49, _50, _51, _52, _53, _54, _55, _56, \
    _57, _58, _59, _60, _61, _62, _63, _64, X, ...) X
#endif
