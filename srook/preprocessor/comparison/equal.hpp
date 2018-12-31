// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_PREPROCESSOR_EQUAL_HPP
#define INCLUDED_SROOK_PREPROCESSOR_EQUAL_HPP

#include <srook/preprocessor/comparison/not_equal.hpp>
#include <srook/preprocessor/not.hpp>

#ifndef _MSC_VER
#   define SROOK_PP_EQUAL(x, y) SROOK_PP_NOT(SROOK_PP_NOT_EQUAL(x, y))
#else
#   define SROOK_PP_EQUAL(x, y) SROOK_PP_EQUAL_I(x, y)
#   define SROOK_PP_EQUAL_I(x, y) SROOK_PP_NOT(SROOK_PP_NOT_EQUAL(x, y))
#endif

#endif
