// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_FORCE_INLINE_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_FORCE_INLINE_HPP

#if defined(_MSC_VER)
#	define SROOK_FORCE_INLINE __force_inline
#	define SROOK_ALWAYS_INLINE SROOK_FORCE_INLINE
#elif (defined(__GNUC__) && (__GNUC__ > 3)) || defined(__clang__)
#	define SROOK_FORCE_INLINE inline __attribute__((__always_inline__))
#	define SROOK_ALWAYS_INLINE SROOK_FORCE_INLINE
#else
#	define SROOK_FORCE_INLINE inline
#	define SROOK_ALWAYS_INLINE SROOK_FORCE_INLINE
#endif

#endif
