// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_USES_ALLOCATOR_HPP
#define INCLUDED_SROOK_MEMORY_USES_ALLOCATOR_HPP

#include <srook/config/feature.hpp>
#include <srook/config/cpp_predefined.hpp> 
#include <srook/utility/void_t.hpp>
#include <srook/type_traits.hpp>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

struct erased_tag {};

template <class Alloc, class T>
struct is_erased_or_convertible 
	: public type_traits::detail::Lor<is_same<T, erased_tag>, is_convertible<Alloc, T>> {};

struct allocator_arg_t { explicit allocator_arg_t () SROOK_DEFAULT };

SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST allocator_arg_t allocator_arg = allocator_arg_t();

template <class T, class Alloc, class = SROOK_DEDUCED_TYPENAME voider<void>::type>
struct uses_allocator_impl : public SROOK_FALSE_TYPE {};

template <class T, class Alloc>
struct uses_allocator_impl<T, Alloc, SROOK_DEDUCED_TYPENAME voider<SROOK_DEDUCED_TYPENAME T::allocator_type>::type>
	: public is_erased_or_convertible<Alloc, SROOK_DEDUCED_TYPENAME T::allocator_type> {};

} // namespace detail

using detail::allocator_arg_t;
using detail::allocator_arg;

template <class T, class Alloc>
struct uses_allocator : public detail::uses_allocator_impl<T, Alloc>::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace memory

using memory::allocator_arg_t;
using memory::allocator_arg;
using memory::uses_allocator;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class Alloc>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool uses_allocator_v = uses_allocator<T, Alloc>::value;
#endif

} // namespace srook

#endif
