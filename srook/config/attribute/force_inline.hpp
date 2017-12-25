// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_FORCE_INLINE_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_FORCE_INLINE_HPP

#if defined(_MSC_VER)
#	define SROOK_FORCE_INLINE __force_inline
#elif (defined(__GNUC__) && (__GNUC__ > 3)) || defined(__clang__)
#	define SROOK_FORCE_INLINE inline __attribute__((__always_inline__))
#elif (defined(__BORLANDC__) || defined(__WATCOMC__))
#   define SROOK_FORCE_INLINE __inline
#else
#	define SROOK_FORCE_INLINE inline
#endif

#define SROOK_ALWAYS_INLINE SROOK_FORCE_INLINE

#endif
