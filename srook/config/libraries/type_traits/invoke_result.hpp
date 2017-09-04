// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_LIBRARIES_TYPE_TRAITS_INVOKE_RESULT_HPP
#define INCLUDED_SROOK_CONFIG_LIBRARIES_TYPE_TRAITS_INVOKE_RESULT_HPP
#include <type_traits>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>

#if SROOK_CPLUSPLUS <= SROOK_CPLUSPLUS14_CONSTANT
#	define SROOK_INVOKE_RESULT_NO_ARGUMENT(F) std::result_of<F()>
#	define SROOK_INVOKE_RESULT(F, ...) std::result_of<F(__VA_ARGS__)>
#elif (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT) && defined(__clang__)
#	if (__clang_major__ * 100 + __clang_minor__ * 10 + __clang_patchlevel__) >= 600
#		define SROOK_INVOKE_RESULT_NO_ARGUMENT(F) std::result_of<F()>
#		define SROOK_INVOKE_RESULT(F, ...) std::result_of<F(__VA_ARGS__)>
#	else
#		define SROOK_INVOKE_RESULT_NO_ARGUMENT(F) std::result_of<F()> // if clang support invoke_result, that will change...
#		define SROOK_INVOKE_RESULT(F, ...) std::result_of<F(__VA_ARGS__)>
#	endif
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#	define SROOK_INVOKE_RESULT_NO_ARGUMENT(F) std::invoke_result<F>
#	define SROOK_INVOKE_RESULT(F, ...) std::invoke_result<F,__VA_ARGS__>
#endif

#endif
