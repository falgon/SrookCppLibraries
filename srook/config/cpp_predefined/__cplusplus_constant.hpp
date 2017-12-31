// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_CPP_PREDEFINED___CPLUSPLUS_CONSTANT_HPP
#define INCLUDED_SROOK_CONFIG_CPP_PREDEFINED___CPLUSPLUS_CONSTANT_HPP

#define SROOK_CPLUSPLUS98_CONSTANT 199711L
#define SROOK_CPLUSPLUS11_CONSTANT 201103L
#define SROOK_CPLUSPLUS14_CONSTANT 201402L
#define SROOK_CPLUSPLUS17_CONSTANT 201703L
#define SROOK_CPLUSPLUS20_CONSTANT
#define SROOK_CPLUSPLUS23_CONSTANT
#define SROOK_CPLUSPLUS26_CONSTANT

#ifdef __cplusplus
#	if SROOK_CPLUSPLUS98_CONSTANT == __cplusplus
#		define SROOK_CPPSTD_VER 98
#	elif SROOK_CPLUSPLUS11_CONSTANT == __cplusplus
#		define SROOK_CPPSTD_VER 11
#	elif SROOK_CPLUSPLUS14_CONSTANT == __cplusplus
#		define SROOK_CPPSTD_VER 14
#	elif SROOK_CPLUSPLUS17_CONSTANT == __cplusplus
#		define SROOK_CPPSTD_VER 17
#	else
#		define SROOK_CPPSTD_VER __cplusplus
#	endif
#else
#	error "__cplusplus macro is not defined"
#endif

#endif
