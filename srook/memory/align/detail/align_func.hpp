// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALIGN_DETAIL_ALIGN_FUNC_HPP
#define INCLUDED_SROOK_MEMORY_ALIGN_DETAIL_ALIGN_FUNC_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/config/nullptr.hpp>
#include <srook/memory/align/detail/is_alignment.hpp>
#if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#   include <memory>
#endif

SROOK_NESTED_NAMESPACE(srook, memory, alignment) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

#if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)

using std::align;

#else

SROOK_FORCE_INLINE void* align(std::size_t a, std::size_t s, void*& p, std::size_t& space)
{
    assert(detail::is_alignment(a));
    if (s <= space) {
        char* const pt = reinterpret_cast<char*>(~(a - 1) & (reinterpret_cast<std::size_t>(p) + a - 1));
        std::size_t n = space - (pt - static_cast<char*>(p));
        if (s <= n) {
            p = pt;
            space = n;
            return pt;
        }
    }
    return SROOK_NULLPTR;
}

#endif

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(alignment, memory, srook)
#endif
