// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_PACKED_SPECIFY_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_PACKED_SPECIFY_HPP

#if defined(__GNUC__) || defined(__clang__)
#   define SROOK_PACKED_SPECIFY(SPS_DECL) SPS_DECL __attribute__((__packed__))
#elif defined(__arm__)
#   define SROOK_PACKED_SPECIFY(SPS_DECL) SPS_DECL __packed
#elif defined(_MSC_VER)
#   define SROOK_PACKED_SPECIFY(SPS_DECL) __pragma(pack(push, 1)) SPS_DECL __pragma(pack(ppo))
#endif

#endif
