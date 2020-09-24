// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_RESOURCE_GLOBAL_MEMORY_RESOURCES_HPP
#define INCLUDED_SROOK_MEMORY_RESOURCE_GLOBAL_MEMORY_RESOURCES_HPP

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <atomic>
#include <srook/memory_resource/config.hpp>
#include <srook/memory_resource/resource_adaptor.hpp>

namespace srook {
namespace pmr {
SROOK_INLINE_NAMESPACE(v1)

SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type 
new_delete_resource() SROOK_NOEXCEPT_TRUE;

namespace detail {

SROOK_FORCE_INLINE 
std::atomic<SROOK_DEDUCED_TYPENAME add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type>& 
get_default_resource()
{
    typedef SROOK_DEDUCED_TYPENAME add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type core_resource_pointer_type;
    static std::atomic<core_resource_pointer_type> default_resource(new_delete_resource());
    return default_resource;
}

template <class Allocator>
class null_memory_resource_ : public memory_resource {
    typedef memory_resource base_type;
    typedef SROOK_DEDUCED_TYPENAME core_type<has_base_type<base_type>::value>::type core_resource_type;
protected:
    void* do_allocate(std::size_t, std::size_t) SROOK_OVERRIDE { SROOK_THROW std::bad_alloc(); }
    void do_deallocate(void*, std::size_t, std::size_t) SROOK_OVERRIDE {}
    bool do_is_equal(const core_resource_type& other) const SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE { return this == &other; }
};

} // namespace detail

SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type
new_delete_resource() SROOK_NOEXCEPT_TRUE
{
    typedef SROOK_DEDUCED_TYPENAME add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type core_resource_pointer_type;
    static resource_adaptor<std::allocator<char>> r;
    return static_cast<core_resource_pointer_type>(&r);
}

SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type
null_memory_resource() SROOK_NOEXCEPT_TRUE
{
    typedef SROOK_DEDUCED_TYPENAME add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type core_resource_pointer_type;
    static detail::null_memory_resource_<void> r;
    return static_cast<core_resource_pointer_type>(&r);
}

SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type
get_default_resource() SROOK_NOEXCEPT_TRUE
{
    return detail::get_default_resource().load();
}

SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type
set_default_resource(SROOK_DEDUCED_TYPENAME add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type r) 
SROOK_NOEXCEPT_TRUE
{
    return detail::get_default_resource().exchange(r ? r : new_delete_resource());
}

SROOK_INLINE_NAMESPACE_END
} // namespace pmr
} // namespace srook

#endif
#endif
