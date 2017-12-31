// Inspired by p0653r1
// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_TO_ADDRESS_HPP
#define INCLUDED_SROOK_MEMORY_TO_ADDRESS_HPP
#include <srook/config/attribute/force_inline.hpp>
#include <srook/memory/pointer_traits.hpp>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

template <class> struct pointer_traits;

template <class T>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T* to_address(T* ptr) SROOK_NOEXCEPT_TRUE { return ptr; }

template <class Ptr>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME pointer_traits<Ptr>::element_type* to_address(const Ptr& ptr)
SROOK_NOEXCEPT(ptr.operator->())
{
    return to_address(ptr.operator->());
}

SROOK_INLINE_NAMESPACE_END
} // namespace memory

using memory::to_address;

} // namespace srook

#endif
