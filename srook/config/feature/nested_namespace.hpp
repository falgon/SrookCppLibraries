// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_NESTED_NAMESPACE_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_NESTED_NAMESPACE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config/cpp_predefined.hpp>
#include <srook/preprocessor.hpp>
#include <srook/preprocessor/detail/loop_delim.hpp>
#include <srook/preprocessor/detail/loop_args_delim.hpp>


#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#   define SROOK_PP_SCOPE_RESOLUTION_OPERATOR ::
#   define SROOK_DEF_NSF(X, ...) SROOK_PP_AT_##X(__VA_ARGS__)
#   define SROOK_DECL_NS_APPLY(X, ...) SROOK_PP_LOOP_ARGS_DELIM(SROOK_DEF_NSF, X, SROOK_PP_SCOPE_RESOLUTION_OPERATOR, __VA_ARGS__)
#   define SROOK_DECL_NS(IGNORE, ...) SROOK_DECL_NS_APPLY(SROOK_PP_VA_COUNT(__VA_ARGS__), __VA_ARGS__)
#   define SROOK_NESTED_NAMESPACE(...)\
        SROOK_PP_IF_ELSE(SROOK_PP_EQUAL(SROOK_PP_VA_COUNT(__VA_ARGS__), 1))\
        (namespace __VA_ARGS__)\
        (namespace SROOK_PP_AT_1(__VA_ARGS__) :: SROOK_DECL_NS(__VA_ARGS__))
#   define SROOK_NESTED_NAMESPACE_END(...)
#else
#   define SROOK_START_DELIM {
#   define SROOK_DEF_NSCOPE(X, ...) namespace SROOK_PP_AT_##X(__VA_ARGS__)
#   define SROOK_DECL_NS_APPLY(X, ...) SROOK_PP_LOOP_ARGS_DELIM(SROOK_DEF_NSCOPE, X, SROOK_START_DELIM, __VA_ARGS__)
#   define SROOK_DECL_NS(IGNORE, ...) SROOK_DECL_NS_APPLY(SROOK_PP_VA_COUNT(__VA_ARGS__), __VA_ARGS__)
#   define SROOK_NESTED_NAMESPACE(...)\
        SROOK_PP_IF_ELSE(SROOK_PP_EQUAL(SROOK_PP_VA_COUNT(__VA_ARGS__), 1))\
        (namespace __VA_ARGS__)\
        (namespace SROOK_PP_AT_1(__VA_ARGS__) { SROOK_DECL_NS(__VA_ARGS__))
#   define SROOK_END_DELIM }
#   define SROOK_DEF_NSCOPE_CLOSE(X)
#   define SROOK_CLOSE_NS_APPLY(X, ...) SROOK_PP_LOOP_DELIM(SROOK_DEF_NSCOPE_CLOSE, X, SROOK_END_DELIM)
#   define SROOK_CLOSE_NS(IGNORE, ...) SROOK_CLOSE_NS_APPLY(SROOK_PP_VA_COUNT(__VA_ARGS__), __VA_ARGS__)
#   define SROOK_NESTED_NAMESPACE_END(...)\
        SROOK_PP_IF_ELSE(SROOK_PP_EQUAL(SROOK_PP_VA_COUNT(__VA_ARGS__), 1))\
        (SROOK_END_DELIM)\
        (SROOK_END_DELIM SROOK_CLOSE_NS(__VA_ARGS__))
#endif

#endif
