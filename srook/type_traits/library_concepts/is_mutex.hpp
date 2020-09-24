// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_MUTEX_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_MUTEX_HPP
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/library_concepts/LOCK.hpp>
#include <srook/type_traits/is_default_constructible.hpp>
#include <srook/type_traits/is_destructible.hpp>
#include <srook/type_traits/is_copyable.hpp>
#include <srook/type_traits/is_movable.hpp>
#include <srook/type_traits/conjunction.hpp>
#include <srook/type_traits/detail/logical.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class Mutex>
struct is_mutex
: conditional<
	conjunction<
	 	is_default_constructible<Mutex>,
		is_destructible<Mutex>,
		detail::Lnot<is_copyable<Mutex>>,
		detail::Lnot<is_movable<Mutex>>
	>::value,
	SROOK_TRUE_TYPE, SROOK_FALSE_TYPE
>::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_mutex;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_mutex_v = is_mutex<T>::value;
#endif

} // namespace srook

#endif
#endif
