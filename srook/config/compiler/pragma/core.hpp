// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_COMPILER_PRAGMA_HPP
#define INCLUDED_SROOK_CONFIG_COMPILER_PRAGMA_HPP

#include <srook/config/compiler/ILE.hpp>
#include <srook/config/environment/os.hpp>

#if SROOK_COMPILER_IS_ILE
#	define SROOK_HAS_PRAGMA_PUSH_POP_MACRO 0
#else
#	define SROOK_HAS_PRAGMA_PUSH_POP_MACRO 1
#endif

#if SROOK_HAS_PRAGMA_PUSH_POP_MACRO
#	ifdef _MSC_VER
#		define SROOK_PUSH_MACROS\
			__pragma(push_macro("min"))\
			__pragma(push_macro("max"))
#		define SROOK_POP_MACROS\
			__pragma(pop_macro("min"))\
			__pragma(pop_macro("max"))
#	else
#		define SROOK_PUSH_MACROS\
			_Pragma("push_macro(\"min\")")\
			_Pragma("push_macro(\"max\")")
#		define SROOK_POP_MACROS\
			_Pragma("pop_macro(\"min\")")\
			_Pragma("pop_macro(\"max\")")
#	endif
#else
#	define SROOK_PUSH_MACROS
#	define SROOK_POP_MACROS
#endif

#endif
