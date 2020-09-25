// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_PREPROCESSOR_BOOL_HPP
#define INCLUDED_SROOK_PREPROCESSOR_BOOL_HPP

#include <srook/preprocessor/not.hpp>

#define SROOK_PP_BOOL(X) SROOK_PP_NOT(SROOK_PP_NOT(X))

#endif
