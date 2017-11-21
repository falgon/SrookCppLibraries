// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_LOCK_IS_TIMEDLOCKABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_LOCK_IS_TIMEDLOCKABLE_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

#include <srook/type_traits/library_concepts/LOCK/is_lockable.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/mutex.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class, class = typename voider<>::type>
struct is_timedlockable : SROOK_FALSE_TYPE {};

template <class TimedLockable>
struct is_timedlockable<
	TimedLockable, 
	typename voider<
        decltype(declval<TimedLockable>().try_lock_for(declval<mutexes::includes::chrono::duration<double>>())), 
        decltype(declval<TimedLockable>().try_lock_until(declval<mutexes::includes::chrono::system_clock::time_point>()))
    >::type
> : conditional<is_lockable<TimedLockable>::value, SROOK_TRUE_TYPE, SROOK_FALSE_TYPE>::type {};


SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_timedlockable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class TimedLockable>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_timedlockable_v = is_timedlockable<TimedLockable>::value;
#endif

} // namespace srook

#endif
#endif
