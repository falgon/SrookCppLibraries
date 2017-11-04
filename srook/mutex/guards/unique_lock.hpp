// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MUTEX_GUARDS_UNIQUE_LOCK_HPP
#define INCLUDED_SROOK_MUTEX_GUARDS_UNIQUE_LOCK_HPP

#include <srook/config/libraries/nullptr.hpp>
#include <srook/config/user_config.hpp>
#include <srook/memory/addressof.hpp>
#include <srook/mutex/guards/detail/lock_tags.hpp>
#include <srook/mutex/includes/lib.hpp>
#include <srook/type_traits/library_concepts/is_mutex.hpp>
#include <srook/utility/move.hpp>
#include <srook/utility/noncopyable.hpp>

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

template <class Mutex>
class SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT unique_lock
#if !defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE) && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
    : private noncopyable<unique_lock<Mutex> >
#endif
{
public:
    typedef Mutex mutex_type;
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_STATIC_ASSERT(is_mutex<Mutex>::value, "The template argument must be Mutex");
#endif
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock() SROOK_NOEXCEPT_TRUE : m_device(SROOK_NULLPTR), owns(false)
    {
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    explicit unique_lock(mutex_type& m) : m_device(srook::addressof(m)), owns(false)
    {
        lock();
        owns = true;
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(mutex_type& m, includes::defer_lock_t) SROOK_NOEXCEPT_TRUE : m_device(srook::addressof(m)), owns(false) {}
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(mutex_type& m, includes::try_to_lock_t) : m_device(srook::addressof(m)), owns(m_device->try_lock()) {}
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(mutex_type& m, includes::adopt_lock_t) SROOK_NOEXCEPT_TRUE : m_device(srook::addressof(m)), owns(true) {}

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(mutex_type& m, defer_lock_t) SROOK_NOEXCEPT_TRUE : m_device(srook::addressof(m)), owns(false) {}
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(mutex_type& m, try_to_lock_t) : m_device(srook::addressof(m)), owns(m_device->try_lock()) {}
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(mutex_type& m, adopt_lock_t) SROOK_NOEXCEPT_TRUE : m_device(srook::addressof(m)), owns(true) {}

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    ~unique_lock()
    {
        if (owns) unlock();
    }

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(unique_lock&& u) SROOK_NOEXCEPT_TRUE : m_device(u.m_device), owns(u.owns)
    {
        u.m_device = SROOK_NULLPTR;
        u.owns = false;
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock& operator=(unique_lock&& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        unique_lock(srook::move(u)).swap(*this);
        u.m_device = SROOK_NULLPTR;
        u.owns = false;

        return *this;
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(includes::unique_lock<mutex_type>&& u) SROOK_NOEXCEPT_TRUE : m_device(u.mutex()), owns(u.owns_lock())
    {
        u.release();
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock& operator=(includes::unique_lock<mutex_type>&& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        m_device = u.mutex();
        owns = u.owns_lock();
        u.release();

        return *this;
    }

#elif defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE)
    // Deprecated because there is not the semantics of rvalue reference in C++03.
    // Behaves similarly to auto_ptr

    SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(unique_lock& u) SROOK_NOEXCEPT_TRUE : m_device(u.m_device), owns(u.owns)
    {
        u.m_device = SROOK_NULLPTR;
        u.owns = false;
    }

    SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock& operator=(unique_lock& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        m_device = u.m_device;
        owns = u.owns;
        u.m_device = SROOK_NULLPTR;
        u.owns = false;
    }

#    if SROOK_HAS_INCLUDE(<boost/thread.hpp>)
    SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(boost::unique_lock<mutex_type>& u) SROOK_NOEXCEPT_TRUE : m_device(u.mutex()), owns(u.owns_lock())
    {
        u.release();
    }

    SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock& operator=(boost::unique_lock<mutex_type>& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        m_device = u.mutex();
        owns = u.owns_lock();
        u.release();

        return *this;
    }
#    endif
#elif !defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE)

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(const utility::cxx03::move_tag<unique_lock>& u) SROOK_NOEXCEPT_TRUE : m_device(u.get().m_device), owns(u.get().owns)
    {
        u.get().m_device = SROOK_NULLPTR;
        u.get().owns = false;
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock& operator=(const utility::cxx03::move_tag<unique_lock>& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        unique_lock(srook::move(u)).swap(*this);
        u.get().m_device = SROOK_NULLPTR;
        u.get().owns = false;

        return *this;
    }

#    if SROOK_HAS_INCLUDE(<boost/thread.hpp>)
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(const utility::cxx03::move_tag<boost::unique_lock<mutex_type> >& u) SROOK_NOEXCEPT_TRUE
        : m_device(u.get().mutex()),
          owns(u.get().owns_lock())
    {
        u.get().release();
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock& operator=(const utility::cxx03::move_tag<boost::unique_lock<mutex_type> >& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        m_device = u.get().mutex();
        owns = u.get().owns_lock();
        u.get().release();

        return *this;
    }

#    endif
#endif

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    void swap(unique_lock& u) SROOK_NOEXCEPT_TRUE
    {
        std::swap(m_device, u.m_device);
        std::swap(owns, u.owns);
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    mutex_type* release() SROOK_NOEXCEPT_TRUE
    {
        mutex_type* ret = m_device;
        m_device = SROOK_NULLPTR;
        owns = false;
        return ret;
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    bool owns_lock() const SROOK_NOEXCEPT_TRUE { return owns; }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    SROOK_EXPLICIT operator bool() const SROOK_NOEXCEPT_TRUE { return owns_lock(); }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    mutex_type* mutex() const SROOK_NOEXCEPT_TRUE { return m_device; }

    template <class Clock, class Duration>
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(mutex_type& m, const includes::chrono::time_point<Clock, Duration>& time)
        : m_device(srook::addressof(m)), owns(m_device->try_lock_until(time))
    {
    }
    template <class Rep, class Period>
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    unique_lock(mutex_type& m, const includes::chrono::duration<Rep, Period>& time)
        : m_device(srook::addressof(m)), owns(m_device->try_lock_for(time))
    {
    }
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    void lock()
    {
        if (!m_device) {
            includes::throw_system_err(includes::errc::operation_not_permitted);
        } else if (owns) {
            includes::throw_system_err(includes::errc::resource_deadlock_would_occur);
        } else {
            m_device->lock();
            owns = true;
        }
    }
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    bool try_lock()
    {
        if (!m_device) {
            includes::throw_system_err(includes::errc::operation_not_permitted);
        } else if (owns) {
            includes::throw_system_err(includes::errc::resource_deadlock_would_occur);
        } else {
            owns = m_device->try_lock();
            return owns;
        }
    }
    template <class Clock, typename Duration>
    SROOK_ATTRIBUTE_INLINE_VISIBILITY bool try_lock_until(const includes::chrono::time_point<Clock, Duration>& time)
    {
        if (!m_device) {
            includes::throw_system_err(includes::errc::operation_not_permitted);
        } else if (owns) {
            includes::throw_system_err(includes::errc::resource_deadlock_would_occur);
        } else {
            owns = m_device->try_lock_until(time);
            return owns;
        }
    }
    template <class Rep, class Period>
    SROOK_ATTRIBUTE_INLINE_VISIBILITY bool try_lock_for(const includes::chrono::duration<Rep, Period>& time)
    {
        if (!m_device) {
            includes::throw_system_err(includes::errc::operation_not_permitted);
        } else if (owns) {
            includes::throw_system_err(includes::errc::resource_deadlock_would_occur);
        } else {
            owns = m_device->try_lock_for(time);
            return owns;
        }
    }
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    void unlock()
    {
        if (!owns) {
            includes::throw_system_err(includes::errc::operation_not_permitted);
        } else if (m_device) {
            m_device->unlock();
            owns = false;
        }
    }

private:
    mutex_type* m_device;
    bool owns;

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    friend inline void swap(unique_lock& lhs, unique_lock& rhs) SROOK_NOEXCEPT_TRUE
    {
        lhs.swap(rhs);
    }
};

#if (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT) && SROOK_CPP_DEDUCTION_GUIDES

template <class M>
unique_lock(unique_lock<M>)->unique_lock<M>;

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes

using mutexes::unique_lock;

} // namespace srook

#endif
