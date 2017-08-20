// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_NO_INLINE_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_NO_INLINE_HPP

#if defined(_MSC_VER)
#define SROOK_NOINLINE __declspec(noinline)
#elif defined(__GNUC__) and (__GNUC__ > 3)
#if defined(__CUDACC__)
#define SROOK_NOINLINE __attribute__((noinline))
#else
#define SROOK_NOINLINE __attribute__((__noinline__))
#endif
#else
#define SROOK_NOINLINE
#endif

#endif
