// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_EXECUTION_CONFIG_HPP
#define INCLUDED_SROOK_EXECUTION_CONFIG_HPP

#ifdef __cpp_lib_experimental_parallel_algorithm
#   include <experimental/execution_policy>
#   define SROOK_HAS_STD_EXPERIMENTAL_EXECUTION_POLICY 1
#endif
#ifdef __lib_cpp_execution
#   include <execution>
#   define SROOK_HAS_STD_EXECUTION 1
#endif

#include <srook/config.hpp>

#endif
