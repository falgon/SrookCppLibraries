// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MEMORY_RESOURCE_MEMORY_RESOURCE_HPP
#define INCLUDED_SROOK_MEMORY_RESOURCE_MEMORY_RESOURCE_HPP

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <memory>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT && SROOK_HAS_INCLUDE(<memory_resource>)
#   include <memory_resource>
#   define SROOK_HAS_STD_MEMORY_RESOURCE 1
#elif SROOK_HAS_INCLUDE(<experimental/memory_resource>)
#   include <experimental/memory_resource>
#   define SROOK_HAS_STD_EXPERIMENTAL_MEMORY_RESOURCE 1
#   define SROOK_HAS_STD_FUNDAMENTALV1_MEMORY_RESOURCE 1
#endif
#include <srook/type_traits.hpp>

namespace srook {
namespace pmr {
SROOK_INLINE_NAMESPACE(v1)

#if defined(SROOK_HAS_STD_MEMORY_RESOURCE) || defined(SROOK_HAS_STD_EXPERIMENTAL_MEMORY_RESOURCE)
class memory_resource : public
#   ifdef SROOK_HAS_STD_MEMORY_RESOURCE
std::pmr::memory_resource
#   elif defined(SROOK_HAS_STD_EXPERIMENTAL_MEMORY_RESOURCE)
std::experimental::pmr::memory_resource
#   endif
{
public:
    typedef 
#ifdef SROOK_HAS_STD_MEMORY_RESOURCE
        std::pmr::memory_resource
#elif defined(SROOK_HAS_STD_EXPERIMENTAL_MEMORY_RESOURCE)
        std::experimental::pmr::memory_resource
#endif
        base_type;
protected:
    static SROOK_CONSTEXPR std::size_t max_align = SROOK_ALIGN_OF(std::max_align_t);
public:
    virtual ~memory_resource() SROOK_OVERRIDE {}
    using base_type::allocate;
    using base_type::deallocate;
    using base_type::is_equal;
protected:
    virtual void* do_allocate(std::size_t, std::size_t) SROOK_OVERRIDE = 0;
    virtual void do_deallocate(void*, std::size_t, std::size_t) SROOK_OVERRIDE = 0;
    virtual bool do_is_equal(const base_type&) const SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE = 0;
#if 0 // C++20 feature
    std::strong_equality operator<=>(const memory_resource& other) const SROOK_NOEXCEPT_TRUE
    {
        return this <=> &other == 0 ? this <=> &other : is_equal(other) ? std::strong_equality::equal : std::strong_equality::unequal;
    }
#endif
};
#else
class memory_resource {
protected:
    static SROOK_CONSTEXPR std::size_t max_align = SROOK_ALIGN_OF(std::max_align_t);
public:
    virtual ~memory_resource() {}

    SROOK_FORCE_INLINE void* allocate(std::size_t bytes, std::size_t alignment = max_align)
    {
        return do_allocate(bytes, alignment);
    }

    SROOK_FORCE_INLINE void deallocate(void* p, std::size_t bytes, std::size_t alignment = max_align)
    {
        return do_deallocate(p, bytes, alignment);
    }

    SROOK_FORCE_INLINE bool is_equal(const memory_resource& other) const SROOK_NOEXCEPT_TRUE
    {
        return do_is_equal(other);
    }
protected:
    virtual void* do_allocate(std::size_t, std::size_t) = 0;
    virtual void do_deallocate(void*, std::size_t, std::size_t) = 0;
    virtual bool do_is_equal(const memory_resource&) const SROOK_NOEXCEPT_TRUE = 0;
#if 0 // C++20 feature
    std::strong_equality operator<=>(const memory_resource& other) const SROOK_NOEXCEPT_TRUE
    {
        return this <=> &other == 0 ? this <=> &other : is_equal(other) ? std::strong_equality::equal : std::strong_equality::unequal;
    }
#endif
};

#if 1
SROOK_FORCE_INLINE bool operator==(const memory_resource& lhs, const memory_resource& rhs) SROOK_NOEXCEPT_TRUE
{
    return &lhs == &rhs || lhs.is_equal(rhs);
}

SROOK_FORCE_INLINE bool operator!=(const memory_resource& lhs, const memory_resource& rhs) SROOK_NOEXCEPT_TRUE
{
    return !(lhs == rhs);
}
#endif
#endif

namespace detail {

SROOK_TT_DEF_HAS_TYPE_IMPL(base_type);
SROOK_TT_DEF_HAS_TYPE(base_type);

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} // namespace pmr
} // namespace srook

#endif
#endif
