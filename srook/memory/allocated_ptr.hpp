// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALLOCATED_PTR_HPP
#define INCLUDED_SROOK_MEMORY_ALLOCATED_PTR_HPP

#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <srook/memory/pointer_traits.hpp>
#include <srook/memory/to_address.hpp>
#include <memory>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

template <class Allocator>
struct allocated_ptr {
	typedef SROOK_DEDUCED_TYPENAME std::allocator_traits<Allocator>::pointer pointer;
	typedef SROOK_DEDUCED_TYPENAME std::allocator_traits<Allocator>::value_type value_type;

	allocated_ptr(Allocator& a, pointer ptr) SROOK_NOEXCEPT_TRUE
		: alloc_(srook::addressof(a)), ptr_(ptr) {}

	template <class Ptr, SROOK_REQUIRES(is_same<Ptr, value_type*>::value)>
	allocated_ptr(Allocator& a, Ptr ptr)
		: alloc_(srook::addressof(a)), ptr_(pointer_traits<pointer>::pointer_to(*ptr)) {}

	allocated_ptr(allocated_ptr&& other)
		: alloc_(other.alloc_), ptr_(other.ptr_)
	{
		other.ptr_ = SROOK_NULLPTR;
	}

	~allocated_ptr()
	{
		if (ptr_) std::allocator_traits<Allocator>::deallocate(*alloc_, ptr_, 1);
	}

	allocated_ptr& operator=(SROOK_NULLPTR_T) SROOK_NOEXCEPT_TRUE
	{
		ptr_ = SROOK_NULLPTR;
		return *this;
	}

	value_type* get() { return srook::to_address(ptr_); }
private:
	Allocator* alloc_;
	pointer ptr_;
};

template <class Allocator>
allocated_ptr<Allocator> allocate_guarded(Allocator& a)
{
	return { a, std::allocator_traits<Allocator>::allocate(a, 1) };
}

SROOK_INLINE_NAMESPACE_END
} // namespace memory
} // namespace srook

#endif
