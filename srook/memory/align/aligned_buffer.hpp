// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALIGNED_BUFFER_HPP
#define INCLUDED_SROOK_MEMORY_ALIGNED_BUFFER_HPP

#include <srook/config.hpp>
#include <srook/type_traits/aligned_storage.hpp>
#include <srook/type_traits/alignment_of.hpp>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct aligned_buffer : public srook::aligned_storage<sizeof(T), srook::alignment_of<T>::value> {
	SROOK_DEDUCED_TYPENAME srook::aligned_storage<sizeof(T), srook::alignment_of<T>::value> storage;

	void* addr() SROOK_NOEXCEPT_TRUE { return static_cast<void*>(&storage); }
	const void* addr() const SROOK_NOEXCEPT_TRUE { return static_cast<const void*>(&storage); }
	T* ptr() SROOK_NOEXCEPT_TRUE { return static_cast<T*>(addr()); }
	const T* ptr() const SROOK_NOEXCEPT_TRUE{ return static_cast<const T*>(addr()); }
};

SROOK_INLINE_NAMESPACE_END
} // namespace memory
} // namespace srook

#endif
