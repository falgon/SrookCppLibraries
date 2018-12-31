// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_LOCK_IS_BASIC_LOCKABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_LOCK_IS_BASIC_LOCKABLE_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/declval.hpp>
#include <srook/utility/void_t.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class, class = typename voider<>::type>
struct is_basic_lockable : SROOK_FALSE_TYPE {};

template <class BasicLockable>
struct is_basic_lockable<
	BasicLockable, 
	typename voider<decltype(declval<BasicLockable>().lock()), decltype(declval<BasicLockable>().unlock())>::type
> : SROOK_TRUE_TYPE {};


SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_basic_lockable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class BasicLockable>
SROOK_INLINE_VARIABLE constexpr bool is_basic_lockable_v = is_basic_lockable<BasicLockable>::value;
#endif

} // namespace srook

#endif
#endif
