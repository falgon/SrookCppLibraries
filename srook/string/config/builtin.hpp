// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_STRING_CONFIG_BUILTIN_HPP
#define INCLUDED_SROOK_STRING_CONFIG_BUILTIN_HPP

#include <srook/config/user_config.hpp>

#if !defined(SROOK_CONFIG_DISABLE_BUILTIN_STRING_FUNCTION) && !defined(__clang__)
#define SROOK_USE_BUILTIN_STRING_FUNCTION 1
#else
#define SROOK_USE_BUILTIN_STRING_FUNCTION 0
#endif

#endif
