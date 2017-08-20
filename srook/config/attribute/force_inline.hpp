// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_FORCE_INLINE_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_FORCE_INLINE_HPP

#if defined(_MSC_VER)
#define SROOK_FORCE_INLINE __force_inline
#elif defined(__GNUC__) && (__GNUC__ > 3)
#define SROOK_FORCE_INLINE inline __attribute__((__always_inline__))
#else
#define SROOK_FORCE_INLINE inline
#endif

#endif
