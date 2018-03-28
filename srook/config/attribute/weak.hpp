// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_WEAK_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_WEAK_HPP

#if defined(__GNUC__) || defined(__clang__)
#   define SROOK_ATTRIBUTE_WEAK  __attribute__((weak))
#elif _MSC_VER
#   define SROOK_ATTRIBUTE_WEAK __declspec(selectany)
#endif

#endif
