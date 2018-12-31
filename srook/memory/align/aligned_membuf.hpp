// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALIGNED_MEMBUF_HPP
#define INCLUDED_SROOK_MEMORY_ALIGNED_MEMBUF_HPP

#include <srook/config.hpp>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct aligned_membuf {
	aligned_membuf() SROOK_DEFAULT
	aligned_membuf(SROOK_NULLPTR_T) {}

	SROOK_FORCE_INLINE void* addr() SROOK_NOEXCEPT_TRUE { return static_cast<void*>(&storage_); }
	SROOK_FORCE_INLINE const void* addr() const SROOK_NOEXCEPT_TRUE { return static_cast<const void*>(&storage_); }
	SROOK_FORCE_INLINE T* ptr() SROOK_NOEXCEPT_TRUE { return static_cast<T*>(addr()); }
	SROOK_FORCE_INLINE const T* ptr() const SROOK_NOEXCEPT_TRUE { return static_cast<const T*>(addr()); }
public:
	struct Type { T t_; };
	SROOK_ATTRIBUTE_ALIGNED_X(SROOK_ALIGN_OF(SROOK_DEDUCED_TYPENAME Type::T)) unsigned char storage_[sizeof(T)];
};

SROOK_INLINE_NAMESPACE_END
} // namespace memory
} // namespace srook

#endif
