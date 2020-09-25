// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
// resource_adaptor is NOT standart included
#ifndef INCLUDED_SROOK_MEMORY_RESOURCE_RESOURCE_ADAPTOR_HPP
#define INCLUDED_SROOK_MEMORY_RESOURCE_RESOURCE_ADAPTOR_HPP

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/utility.hpp>
#include <srook/memory_resource/config.hpp>
#include <srook/memory_resource/memory_resource.hpp>

namespace srook {
namespace pmr {
SROOK_INLINE_NAMESPACE(v1)

template <class Allocator>
class resource_adaptor : public memory_resource {
public:
    typedef Allocator allocator_type;
    typedef std::allocator_traits<allocator_type> allocator_traits_type;
    typedef SROOK_DEDUCED_TYPENAME allocator_traits_type::value_type value_type;
    
    SROOK_CONSTEXPR resource_adaptor() SROOK_DEFAULT

    explicit SROOK_CONSTEXPR resource_adaptor(const Allocator& a) : alloc_(a) {}
    explicit SROOK_CONSTEXPR resource_adaptor(Allocator&& a) : alloc_(srook::move(a)) {}
    
    SROOK_CONSTEXPR_OR_CONST allocator_type& get_allocator() const SROOK_NOEXCEPT_TRUE { return alloc_; }
protected:
    virtual void* do_allocate(std::size_t bytes, std::size_t alignment) SROOK_OVERRIDE
    {
        typedef SROOK_DEDUCED_TYPENAME allocator_traits_type::template rebind_alloc<char> aligned_alloc_type;
        std::size_t new_size = aligned_size(bytes, is_supported(alignment) ? alignment : memory_resource::max_align);
        return aligned_alloc_type(alloc_).allocate(new_size);
    }

    virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) SROOK_OVERRIDE
    {
        typedef SROOK_DEDUCED_TYPENAME allocator_traits_type::template rebind_alloc<char> aligned_alloc_type;
        std::size_t new_size = aligned_size(bytes, is_supported(alignment) ? alignment : memory_resource::max_align);
        
        typedef SROOK_DEDUCED_TYPENAME allocator_traits_type::template rebind_traits<char>::pointer pointer;
        aligned_alloc_type(alloc_).deallocate(static_cast<pointer>(p), new_size);
    }

    virtual bool do_is_equal(const SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type& other) 
    const SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE
    {
        auto p = dynamic_cast<const resource_adaptor*>(&other);
        return p ? (alloc_ == p->alloc_) : false;
    }

private:
    SROOK_CONSTEXPR static std::size_t aligned_size(std::size_t size, std::size_t alignment) SROOK_NOEXCEPT_TRUE
    {
        return ((size - 1) | (alignment - 1)) + 1;
    }

    SROOK_CONSTEXPR static bool is_supported(std::size_t x) SROOK_NOEXCEPT_TRUE
    {
        return ((x != 0) && !(x & (x - 1)));
    }

    Allocator alloc_;
};

SROOK_INLINE_NAMESPACE_END
} // namespace pmr
} // namespace srook

#endif
#endif
