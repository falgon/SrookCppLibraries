// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_PACKED_END_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_PACKED_END_HPP

#if defined(__GNUC__) || defined(__clang__)
#   ifdef SROOK_PACKED
#       undef SROOK_PACKED
#   endif
#elif defined(__arm__)
#   ifdef SROOK_PACKED
#       undef SROOK_PACKED
#   endif
#elif defined(_MSC_VER)
#   pragma pack(pop)
#   ifdef SROOK_PACKED
#       undef SROOK_PACKED
#   endif
#endif

#endif
