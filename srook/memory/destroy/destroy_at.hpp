// Copyright (C) 2011-2018 Roki. Distributed under the MIT License.
#ifndef INCLUDED_SROOK_MEMORY_DESTORY_DESTROY_AT_HPP
#define INCLUDED_SROOK_MEMORY_DESTORY_DESTROY_AT_HPP

#include <srook/memory/destroy/config.hpp>

#ifdef SROOK_HAS_PRAGMA_ONCE
#   pragma once
#endif

SROOK_NESTED_NAMESPACE(srook, memory) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
SROOK_FORCE_INLINE void destroy_at(T* location)
SROOK_NOEXCEPT(srook::memory::detail::destroy_impl(location))
{
    srook::memory::detail::destroy_impl(location);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(memory, srook)

namespace srook {

using srook::memory::destroy_at;

} // namespace srook
#endif
