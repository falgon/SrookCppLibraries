// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALIGNED_DETAIL_ALIGNED_ALLOC_STD_HPP
#define INCLUDED_SROOK_MEMORY_ALIGNED_DETAIL_ALIGNED_ALLOC_STD_HPP

#include <srook/config.hpp>
#include <memory>

SROOK_NESTED_NAMESPACE(srook, memory, alignment) {
SROOK_INLINE_NAMESPACE(v1)

#if 0 && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT)
using std::aligned_alloc;
#else
using ::aligned_alloc;
#endif

SROOK_FORCE_INLINE void aligned_free(void* pt) SROOK_NOEXCEPT_TRUE
{
    std::free(pt);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(alignment, memory, srook)
#endif
