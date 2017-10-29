// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MUTEX_GUARDS_LOCK_GUARD_HPP
#define INCLUDED_SROOK_MUTEX_GUARDS_LOCK_GUARD_HPP

#include <srook/config/feature/explicit.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/static_assert.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/mutex/detail/lock_tags.hpp>
#include <srook/utility/noncopyable.hpp>
#include <srook/type_traits/library_concepts/is_mutex.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_HAS_INCLUDE(<mutex>)
#    include <mutex>
#elif !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && SROOK_HAS_INCLUDE(<boost/thread.hpp>)
#    include <boost/thread.hpp>
#endif

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

template <class Mutex>
class lock_guard : private noncopyable<lock_guard<Mutex> > {
public:
    typedef Mutex mutex_type;
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_STATIC_ASSERT(is_mutex<Mutex>::value, "The template argument must be Mutex");
#endif
    SROOK_EXPLICIT lock_guard(mutex_type& m) : m_device(m)
    {
        m_device.lock();
    }

    lock_guard(mutex_type& m, adopt_lock_t) SROOK_NOEXCEPT_TRUE : m_device(m) {}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_HAS_INCLUDE(<mutex>)
	lock_guard(mutex_type& m, std::adopt_lock_t) SROOK_NOEXCEPT_TRUE : m_device(m) {}
#elif !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && SROOK_HAS_INCLUDE(<boost/thread.hpp>)
	lock_guard(mutex_type& m, boost::adopt_lock_t) SROOK_NOEXCEPT_TRUE : m_device(m) {}
#endif

    ~lock_guard()
    {
        m_device.unlock();
    }
private:
    Mutex& m_device;
};

SROOK_INLINE_NAMESPACE_END
} // namespace mutex

using mutexes::lock_guard;

} // namespace srook
#endif
