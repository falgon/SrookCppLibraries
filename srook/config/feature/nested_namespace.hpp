// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_NESTED_NAMESPACE_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_NESTED_NAMESPACE_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/preprocessor.hpp>
#include <srook/preprocessor/detail/loop_delim.hpp>
#include <srook/preprocessor/detail/loop_args_delim.hpp>


#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#   define SROOK_PP_SCOPE_RESOLUTION_OPERATOR ::
#   define SROOK_DEF_NSF(X, ...) SROOK_PP_AT_##X(__VA_ARGS__)
#   define SROOK_DECL_NS(X, ...) SROOK_PP_LOOP_ARGS_DELIM(SROOK_DEF_NSF, X, SROOK_PP_SCOPE_RESOLUTION_OPERATOR, __VA_ARGS__)
#   define SROOK_NESTED_NAMESPACE(X, ...)\
        SROOK_PP_IF_ELSE(SROOK_PP_EQUAL(SROOK_PP_VA_COUNT(__VA_ARGS__), 0))\
        (namespace X)\
        (namespace X :: SROOK_DECL_NS(SROOK_PP_VA_COUNT(__VA_ARGS__), __VA_ARGS__))
#   define SROOK_NESTED_NAMESPACE_END(...)
#else
#   define SROOK_START_DELIM {
#   define SROOK_DEF_NSCOPE(X, ...) namespace SROOK_PP_AT_##X(__VA_ARGS__)
#   define SROOK_DECL_NS(X, ...) SROOK_PP_LOOP_ARGS_DELIM(SROOK_DEF_NSCOPE, X, SROOK_START_DELIM, __VA_ARGS__)
#   define SROOK_NESTED_NAMESPACE(X, ...)\
        SROOK_PP_IF_ELSE(SROOK_PP_EQUAL(SROOK_PP_VA_COUNT(__VA_ARGS__), 0))\
        (namespace X)\
        (namespace X { SROOK_DECL_NS(SROOK_PP_VA_COUNT(__VA_ARGS__), __VA_ARGS__))
#   define SROOK_END_DELIM }
#   define SROOK_DEF_NSCOPE_CLOSE(X)
#   define SROOK_CLOSE_NS(X, ...) SROOK_PP_LOOP_DELIM(SROOK_DEF_NSCOPE_CLOSE, X, SROOK_END_DELIM)
#   define SROOK_NESTED_NAMESPACE_END(X, ...)\
        SROOK_PP_IF_ELSE(SROOK_PP_EQUAL(SROOK_PP_VA_COUNT(__VA_ARGS__), 0))\
        (SROOK_END_DELIM)\
        (SROOK_END_DELIM SROOK_CLOSE_NS(SROOK_PP_VA_COUNT(__VA_ARGS__)))
#endif

#endif
