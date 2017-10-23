// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MEMORY_ADDRESS_OF_HPP
#define INCLUDED_SROOK_MEMORY_ADDRESS_OF_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/user_config.hpp>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
SROOK_CONSTEXPR T* addressof(T& r) 
#if SROOK_CONFIG_DISABLE_BUILTIN_ADDRESS_OF 
SROOK_NOEXCEPT_TRUE
#else
noexcept(noexcept(reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(r)))))
#endif
{
	return 
#if SROOK_CONFIG_DISABLE_BUILTIN_ADDRESS_OF
		__builtin_addressof(r)
#else
		reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(r)))
#endif
		;
}

template <class T>
const T* addressof(const T&&) = delete;

SROOK_INLINE_NAMESPACE_END
} // namespace memory

using memory::addressof;

} // namespace srook

#endif
