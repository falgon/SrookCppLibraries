// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_SEMAPHORE_GENERIC_UP_ALL_HPP
#define INCLUDED_SROOK_SEMAPHORE_GENERIC_UP_ALL_HPP

#include <srook/semaphore/generic/down_all.hpp>

namespace srook {
namespace semaphores {
SROOK_INLINE_NAMESPACE(v1)

template <class Semaphore, SROOK_REQUIRES(type_traits::detail::Land<is_downable<Semaphore>, is_upable<Semaphore> >::value)>
void up_all(Semaphore& sm)
{
    SROOK_ST_ASSERT(is_integral<SROOK_DEDUCED_TYPENAME Semaphore::counter_type>::value);
    while (sm.resource() != sm.max()) sm.up();
}

SROOK_INLINE_NAMESPACE_END
} // namespace semaphores
} // namespace srook

#endif
