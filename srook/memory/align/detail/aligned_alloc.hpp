// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALIGN_DETAIL_ALIGNED_ALLOC_HPP
#define INCLUDED_SROOK_MEMORY_ALIGN_DETAIL_ALIGNED_ALLOC_HPP

#ifdef SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_ANDROID
#   include <srook/memory/align/detail/aligned_alloc/anroid.hpp>
#elif defined(SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_MSVC)
#   include <srook/memory/align/detail/aligned_alloc/msvc.hpp>
#elif defined(SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_MACOS)
#   include <srook/memory/align/detail/aligned_alloc/macos.hpp>
#elif defined(SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_POSIX)
#   include <srook/memory/align/detail/aligned_alloc/posix.hpp>
#elif defined(SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_SUNOS)
#   include <srook/memory/align/detail/aligned_alloc/sunos.hpp>
#elif defined(SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_GNU_MM)
#   include <srook/memory/align/detail/aligned_alloc/gnu_mm.hpp>
#elif defined(SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_MM)
#   include <srook/memory/align/detail/aligned_alloc/mm.hpp>
#elif defined(SROOK_MEMORY_ALIGNED_ALLOC_INCLUDE_STD)
#   include <srook/memory/align/detail/aligned_alloc/std.hpp>
#else
#   include <srook/memory/align/detail/aligned_alloc/native.hpp>
#endif

#endif
