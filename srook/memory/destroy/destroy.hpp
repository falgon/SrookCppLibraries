// Copyright (C) 2011-2018 Roki. Distributed under the MIT License.
#ifndef INCLUDED_SROOK_MEMORY_DESTORY_DESTROY_HPP
#define INCLUDED_SROOK_MEMORY_DESTORY_DESTROY_HPP

#include <srook/memory/destroy/config.hpp>

#ifdef SROOK_HAS_PRAGMA_ONCE
#   pragma once
#endif

SROOK_NESTED_NAMESPACE(srook, memory) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <class ForwardIter> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter>
#endif
SROOK_FORCE_INLINE void destroy(ForwardIter first, ForwardIter last)
SROOK_NOEXCEPT(srook::memory::detail::destroy_impl(first, last))
{
    srook::memory::detail::destroy_impl(first, last);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(memory, srook)

namespace srook {

using srook::memory::destroy;

} // namespace srook
#endif
