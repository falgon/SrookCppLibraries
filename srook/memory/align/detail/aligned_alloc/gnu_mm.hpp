// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALIGNED_DETAIL_ALIGNED_ALLOC_GNU_MM_HPP
#define INCLUDED_SROOK_MEMORY_ALIGNED_DETAIL_ALIGNED_ALLOC_GNU_MM_HPP

#include <srook/config.hpp>
#include <srook/memory/align/detail/is_alignment.hpp>
extern "C" {
#include <mm_malloc.h>
}

SROOK_NESTED_NAMESPACE(srook, memory, alignment) {
SROOK_INLINE_NAMESPACE(v1)

SROOK_FORCE_INLINE void* aligned_alloc(std::size_t a, std::size_t size) SROOK_NOEXCEPT_TRUE
{
    assert(detail::is_alignment(a));
    return ::_mm_malloc(size, a);
}

SROOK_FORCE_INLINE void aligned_free(void* p) SROOK_NOEXCEPT_TRUE
{
    ::_mm_free(p);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(alignment, memory, srook)
#endif
