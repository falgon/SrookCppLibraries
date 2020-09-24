// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALIGNED_DETAIL_ALIGNED_ALLOC_NATIVE_HPP
#define INCLUDED_SROOK_MEMORY_ALIGNED_DETAIL_ALIGNED_ALLOC_NATIVE_HPP

#include <srook/config.hpp>
#include <srook/memory/align/detail/is_alignment.hpp>
#include <srook/memory/align/detail/align_func.hpp>
#include <srook/type_traits/alignment_of.hpp>
#include <cstdlib>

SROOK_NESTED_NAMESPACE(srook, memory, alignment) {
SROOK_INLINE_NAMESPACE(v1)

SROOK_FORCE_INLINE void* aligned_alloc(std::size_t a, std::size_t size) SROOK_NOEXCEPT_TRUE
{
    assert(detail::is_alignment(size));
    typedef alignment_of<void*> aof_t;

    if (a < aof_t::value) a = aof_t::value;
    std::size_t n = size + a - aof_t::value;
    void* pt = std::malloc(sizeof(void*) + n);
    if (pt) {
        void* r = static_cast<char*>(pt) + sizeof(void*);
        static_cast<void>(detail::align(a, size, r, n));
        *(static_cast<void**>(r) - 1) = pt;
        pt = r;
    }
    return pt;
}

SROOK_FORCE_INLINE void aligned_free(void* pt) SROOK_NOEXCEPT_TRUE
{
    if (pt) std::free(*(static_cast<void**>(pt) - 1));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(alignment, memory, srook)
#endif
