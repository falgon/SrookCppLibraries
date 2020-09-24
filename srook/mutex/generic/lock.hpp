// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MUTEX_GENERIC_LOCK_HPP
#define INCLUDED_SROOK_MUTEX_GENERIC_LOCK_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPP_VARIADIC_TEMPLATES && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/static_assert.hpp>
#include <srook/mutex/generic/detail/try_locker.hpp>
#include <srook/type_traits/library_concepts/LOCK/is_lockable.hpp>
#include <srook/type_traits/conjunction.hpp>

namespace srook {
namespace cxx11 {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

template <class L1, class L2, class... Ls>
void lock(L1& l1, L2& l2, Ls&... ls)
{
	SROOK_STATIC_ASSERT(is_lockable<L1>::value && is_lockable<L2>::value && conjunction<is_lockable<Ls>...>::value, "Arguments must be lockable");
	for(int index = 0;; index = 0) {
		unique_lock<L1> l(l1);
		detail::try_locker<0, sizeof...(Ls) != 0>::do_try_lock(std::forward_as_tuple(l2, ls...), index);
		if (index == -1) {
			l.release();
			return ;
		}
	}
}

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes

using mutexes::lock;

} // namespace cxx11

using cxx11::lock;

} // namespace srook 


#endif
#endif
