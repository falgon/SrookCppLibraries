// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_PREPROCESSOR_NOT_HPP
#define INCLUDED_SROOK_PREPROCESSOR_NOT_HPP

#include <srook/preprocessor/at.hpp>
#include <srook/preprocessor/concat.hpp>

#ifdef _MSC_VER
#    define SROOK_PP_IS(...) SROOK_PP_INDIRECT(SROOK_PP_AT_2(__VA_ARGS__, 0))
#else
#    define SROOK_PP_IS(...) SROOK_PP_AT_2(__VA_ARGS__, 0)
#endif
#define SROOK_PP_INDIRECT(X) X
#define SROOK_PP_PROBE() ~, 1

#define SROOK_PP_NOT(X) SROOK_PP_IS(SROOK_PP_CONCAT(SROOK_PP_NOT_, X))
#define SROOK_PP_NOT_0 SROOK_PP_PROBE()

#endif
