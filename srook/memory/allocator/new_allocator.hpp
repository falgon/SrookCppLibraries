// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_ALLOCATOR_NEW_ALLOCATOR_HPP
#define INCLUDED_SROOK_MEMORY_ALLOCATOR_NEW_ALLOCATOR_HPP
#include <srook/config.hpp>
#include <srook/utility/move.hpp>
#include <srook/memory/addressof.hpp>
#include <srook/memory/destroy/destroy_at.hpp>
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/utility/move.hpp>
#include <new>

SROOK_NESTED_NAMESPACE(srook, memory, allocators) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
class new_allocator {
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;

    template <class U>
    struct rebind {
        typedef new_allocator<U> other;
    };

    SROOK_FORCE_INLINE SROOK_CONSTEXPR new_allocator() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR new_allocator(const new_allocator&) SROOK_NOEXCEPT_TRUE SROOK_DEFAULT

    template <class U>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR new_allocator(const new_allocator<U>&) SROOK_NOEXCEPT_TRUE {}

    SROOK_FORCE_INLINE pointer address(reference x) const SROOK_NOEXCEPT_TRUE { return srook::addressof(x); }
    SROOK_FORCE_INLINE const_pointer address(const_reference x) const SROOK_NOEXCEPT_TRUE { return srook::addressof(x); }

    SROOK_FORCE_INLINE pointer allocate(size_type n, const void* = static_cast<const void*>(SROOK_NULLPTR))
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    const
#endif
    {
        if (SROOK_UNLIKELY(n > max_size())) SROOK_THROW std::bad_alloc();
#if __cpp_aligned_new
        if (SROOK_ALIGN_OF(T) > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
            return static_cast<T*>(::operator new(n * sizeof(T), std::align_val_t(SROOK_ALIGN_OF(T))));
        }
#endif
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    
    SROOK_FORCE_INLINE void deallocate(pointer p, size_type)
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    const
#endif
    SROOK_NOEXCEPT_TRUE
    {
#if __cpp_aligned_new
        if (SROOK_ALIGN_OF(T) > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
            ::operator delete(p, std::align_val_t(SROOK_ALIGN_OF(T)));
            return ;
        }
#endif
        ::operator delete(p);
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR size_type max_size() const SROOK_NOEXCEPT_TRUE { return size_type(-1) / sizeof(T); }
#if SROOK_CPP_RVALUE_REFERENCES && SROOK_CPP_VARIADIC_TEMPLATES
    template <class U, class... Args>
    SROOK_FORCE_INLINE U* construct(U* p, Args&&... args) 
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    const
#endif
    SROOK_NOEXCEPT(is_nothrow_constructible<U, Args&&...>::value)
    {
        return ::new(static_cast<void*>(p)) U(srook::forward<Args>(args)...);
    }
#else
    SROOK_FORCE_INLINE pointer construct(pointer p, const T& val) 
    {
        return ::new(static_cast<void*>(p)) T(val);
    }
#endif
    template <class U>
    SROOK_FORCE_INLINE void destroy(U* p) 
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    const
#endif
    SROOK_NOEXCEPT_TRUE 
    { srook::memory::destroy_at(p); }

    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator==(const new_allocator&, const new_allocator&) SROOK_NOEXCEPT_TRUE { return true; }
    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator!=(const new_allocator&, const new_allocator&) SROOK_NOEXCEPT_TRUE { return false; }
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(allocators, memory, srook)
#endif
