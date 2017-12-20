// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MEMORY_RESOURCE_CONFIG_HPP
#define INCLUDED_SROOK_MEMORY_RESOURCE_CONFIG_HPP

#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <srook/memory_resource/memory_resource.hpp>

namespace srook {
namespace pmr {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

SROOK_TT_DEF_HAS_TYPE_IMPL(base_type);
SROOK_TT_DEF_HAS_TYPE(base_type);

template <bool>
struct core_type : type_constant<memory_resource> {};
template <>
struct core_type<true> : type_constant<SROOK_DEDUCED_TYPENAME memory_resource::base_type> {};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} // namespace pmr
} // namespace srook

#endif
