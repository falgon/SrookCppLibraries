// Copyright (C) 2011-2019 Roki. Distributed under the MIT License.
#ifndef INCLUDED_SROOK_MEMORY_DESTORY_DESTROY_N_HPP
#define INCLUDED_SROOK_MEMORY_DESTORY_DESTROY_N_HPP

#include <srook/memory/destroy/config.hpp>

#ifdef SROOK_HAS_PRAGMA_ONCE
#   pragma once
#endif

SROOK_NESTED_NAMESPACE(srook, memory) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <class ForwardIter, class Size> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class Size, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class Size>
#endif
SROOK_FORCE_INLINE void destroy(ForwardIter first, Size s)
SROOK_NOEXCEPT(srook::memory::detail::destroy_n_impl(first, s))
{
    srook::memory::detail::destroy_impl(first, s);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(memory, srook)

namespace srook {

using srook::memory::destroy;

} // namespace srook
#endif
