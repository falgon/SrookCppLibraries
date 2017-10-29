// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_LOCK_IS_LOCKABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_LOCK_IS_LOCKABLE_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

#include <srook/type_traits/library_concepts/LOCK/is_basic_lockable.hpp>
#include <srook/type_traits/conditional.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class, class = typename voider<>::type>
struct is_lockable : SROOK_FALSE_TYPE {};

template <class Lockable>
struct is_lockable<
	Lockable, 
	typename voider<decltype(declval<Lockable>().try_lock())>::type
> : conditional<is_basic_lockable<Lockable>::value, SROOK_TRUE_TYPE, SROOK_FALSE_TYPE>::type {};


SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_lockable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class Lockable>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_lockable_v = is_lockable<Lockable>::value;
#endif

} // namespace srook

#endif
#endif
