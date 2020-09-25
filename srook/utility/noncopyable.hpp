// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_UTILITY_NONCOPYABLE_HPP
#define INCLUDED_SROOK_UTILITY_NONCOPYABLE_HPP

#include <srook/utility/enable_copy_move.hpp>

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
class noncopyable : private enable_copy_move<false, false, true, true, noncopyable<T> > {};

SROOK_INLINE_NAMESPACE_END
} // utility

using utility::noncopyable;

} // srook

#endif
