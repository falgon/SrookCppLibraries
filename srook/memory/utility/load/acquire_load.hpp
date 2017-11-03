// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MEMORY_MEMORY_MODEL_ACQUIRE_LOAD_HPP
#define INCLUDED_SROOK_MEMORY_MEMORY_MODEL_ACQUIRE_LOAD_HPP

#include <srook/thread/detail/support.hpp>

namespace srook {
namespace memory {
namespace memory_model {
SROOK_INLINE_NAMESPACE(v1)

template <typename ValueType>
SROOK_ALWAYS_INLINE
ValueType acquire_load(const ValueType* value) 
{
	return
#if SROOK_HAS_THREADS && defined(__ATOMIC_ACQUIRE) && (__has_builtin(__atomic_load_n) || _GNUC_VER >= 407)
		__atomic_load_n(value, __ATOMIC_ACQUIRE)
#else
		*value
#endif
		;
}

SROOK_INLINE_NAMESPACE_END
} // memory_model

using memory_model::acquire_load;

} // memory

using memory::acquire_load;

} // namespace srook
#endif
