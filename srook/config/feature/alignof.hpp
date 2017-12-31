// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_ALIGNOF_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_ALIGNOF_HPP

#include <srook/config/cpp_predefined.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    define SROOK_ALIGN_OF(T) alignof(T)
#elif defined(__GNUC__) || defined(__clang__)
#    define SROOK_ALIGN_OF(T) __alignof__(T)
#elif defined(_MSC_VER)
#    define SROOK_ALIGN_OF(T) __alignof(T)
#endif

#endif
