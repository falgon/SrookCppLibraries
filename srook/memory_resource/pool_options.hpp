// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_RESOURCE_POOL_OPTIONS_HPP
#define INCLUDED_SROOK_MEMORY_RESOURCE_POOL_OPTIONS_HPP

#if defined(_MSC_VER)
#   pragma once
#endif

#include <cstddef>
#include <srook/config.hpp>

namespace srook {
namespace pmr {
SROOK_INLINE_NAMESPACE(v1)

struct pool_options {
    pool_options() : max_blocks_per_chunk(0u), largest_required_pool_block(0u) {}
    std::size_t max_blocks_per_chunk;
    std::size_t largest_required_pool_block;
};

SROOK_INLINE_NAMESPACE_END
} // namespace pmr
} // namespace srook

#endif
