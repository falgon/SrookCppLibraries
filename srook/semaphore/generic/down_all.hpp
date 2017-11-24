// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_SEMAPHORE_GENERIC_DOWN_ALL_HPP
#define INCLUDED_SROOK_SEMAPHORE_GENERIC_DOWN_ALL_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature.hpp>
#include <srook/type_traits.hpp>
#include <srook/utility/declval.hpp>

namespace srook {
namespace semaphores {
SROOK_INLINE_NAMESPACE(v1)

template <class Semaphore, SROOK_REQUIRES(type_traits::detail::Land<is_downable<Semaphore>, is_upable<Semaphore> >::value)>
SROOK_FORCE_INLINE void down_all(Semaphore& sm)
{
    sm.down_all();
}

SROOK_INLINE_NAMESPACE_END
} // namespace semaphores
} // namespace srook

#endif
