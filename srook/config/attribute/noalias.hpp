// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_NO_ALIAS_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_NO_ALIAS_HPP

#include <srook/config/compiler.hpp>

#if defined(__GNUC__) || defined(SROOK_COMPILER_IS_ILE) || defined(_NOALIAS)
#	define SROOK_ATTRIBUTE_NO_ALIAS __attribute__((__malloc__))
#else
#	define SROOK_ATTRIBUTE_NO_ALIAS
#endif

#endif
