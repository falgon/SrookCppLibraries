// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_THREAD_DECL_HPP
#define INCLUDED_SROOK_THREAD_DECL_HPP

#include <srook/thread/detail/thread_base.hpp>
#include <srook/thread/detail/this_thread.hpp>

namespace srook {

using threading::detail::thread;

namespace this_thread {
SROOK_INLINE_NAMESPACE(v1)

using threading::detail::sleep_for;
using threading::detail::sleep_until;
using threading::detail::yield;
using threading::detail::get_id;

SROOK_INLINE_NAMESPACE_END
} // namespace this_thread
} // namespace srook

#endif
