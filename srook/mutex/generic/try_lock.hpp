// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MUTEX_GENERIC_TRY_LOCK_HPP
#define INCLUDED_SROOK_MUTEX_GENERIC_TRY_LOCK_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPP_VARIADIC_TEMPLATES && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/static_assert.hpp>
#include <srook/mutex/generic/detail/try_locker.hpp>
#include <srook/type_traits/conjunction.hpp>
#include <srook/type_traits/library_concepts/LOCK.hpp>

namespace srook {
namespace cxx11 {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

template <class L1, class L2, class... Ls>
int try_lock(L1& l1, L2& l2, Ls&... ls)
{
	SROOK_STATIC_ASSERT(is_lockable<L1>::value && is_lockable<L2>::value && conjunction<Ls...>::value, "Arguments must be lockable");
	int index = 0;
	detail::try_locker<0, true>::do_try_lock(std::forward_as_tuple(l1, l2, ls...), index);
	return index;
}

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes

using mutexes::try_lock;

} // namespace cxx11

using cxx11::try_lock;

} // namespace srook 


#endif
#endif
