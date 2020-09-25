// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_PACKED_BEGIN_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_PACKED_BEGIN_HPP

#if defined(__GNUC__) || defined(__clang__)
#   define SROOK_PACKED __attribute__ ((__packed__))
#elif defined(__arm__)
#   define SROOK_PACKED __packed
#elif defined(_MSC_VER)
#   define SROOK_PACKED
#   pragma pack(push, 1)
#endif

#endif
