// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_GUARDS_LOCK_GUARD_HPP
#define INCLUDED_SROOK_THREAD_GUARDS_LOCK_GUARD_HPP

#include <srook/config/feature/explicit.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/thread/detail/lock_tags.hpp>
#include <srook/utility/noncopyable.hpp>

namespace srook {
namespace thread {
SROOK_INLINE_NAMESPACE(v1)

template <class Mutex>
class lock_guard : private noncopyable<lock_guard<Mutex> > {
public:
    typedef Mutex mutex_type;
    SROOK_EXPLICIT lock_guard(mutex_type& m) : m_device(m)
    {
        m_device.lock();
    }

    lock_guard(mutex_type& m, adopt_lock_t) SROOK_NOEXCEPT_TRUE : m_device(m) {}

    ~lock_guard()
    {
        m_device.unlock();
    }

private:
    Mutex& m_device;
};

SROOK_INLINE_NAMESPACE_END
} // namespace thread

using thread::lock_guard;

} // namespace srook
#endif
