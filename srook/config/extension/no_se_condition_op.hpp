// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_NO_SE_CONDITION_OPERANDS_HPP
#define INCLUDED_SROOK_CONFIG_NO_SE_CONDITION_OPERANDS_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/constexpr.hpp>

#ifdef __GNUC__
#   define SROOK_NO_SE_COND_OP(X, Y) X ? : Y
#elif SROOK_CPP_LAMBDAS && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#   define SROOK_NO_SE_COND_OP(X, Y) [&]() SROOK_CONSTEXPR { SROOK_DECLTYPE(X) r_ = X; return r_ ? r_ : Y; }();
#elif SROOK_CPP_LAMBDAS
#   define SROOK_NO_SE_COND_OP(X, Y) [&]{ SROOK_DECLTYPE(X) r_ = X; return r_ ? r_ : Y; }();
#else
#   error this environment is not supported no se conditional operator
#endif

#endif
