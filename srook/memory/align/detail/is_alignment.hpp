// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALIGNMENT_DETAIL_IS_ALIGNMENT_HPP
#define INCLUDED_SROOK_MEMORY_ALIGNMENT_DETAIL_IS_ALIGNMENT_HPP

#include <srook/memory/align/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, memory, alignment) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {
    
SROOK_CONSTEXPR SROOK_FORCE_INLINE bool is_alignment(std::size_t val) SROOK_NOEXCEPT_TRUE
{
    return (val > 0) && (!(val & (val - 1)));
}

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(alignment, memory, srook)
#endif
