// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_GUARDS_UNIQUE_LOCK_HPP
#define INCLUDED_SROOK_THREAD_GUARDS_UNIQUE_LOCK_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/feature/explicit.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/memory/addressof.hpp>
#include <srook/thread/detail/lock_tags.hpp>
#include <srook/utility/move.hpp>
#include <srook/utility/noncopyable.hpp>

#if (SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>) || SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)) && (SROOK_HAS_INCLUDE(<system_error>) || SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>))

#    if SROOK_HAS_INCLUDE(<chrono>) && SROOK_HAS_INCLUDE(<system_error>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#        include <chrono>
#        include <system_error>
#    elif SROOK_HAS_INCLUDE(<boost/chrono.hpp>) && SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
#        include <boost/chrono.hpp>
#        include <boost/system/system_error.hpp>
#    elif SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>) && SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
#        include <boost/chrono/include.hpp>
#        include <boost/system/system_error.hpp>
#    endif

namespace srook {
namespace thread {
SROOK_INLINE_NAMESPACE(v1)

template <class Mutex>
class unique_lock : private noncopyable<unique_lock<Mutex> > {
public:
    typedef Mutex mutex_type;

    unique_lock() SROOK_NOEXCEPT_TRUE : m_device(0), owns(false)
    {
        lock();
        owns = true;
    }

	SROOK_EXPLICIT unique_lock(mutex_type& m) : m_device(addressof(m)), owns(false) 
	{
		lock();
		owns = true;
	}

    unique_lock(mutex_type& m, defer_lock_t) SROOK_NOEXCEPT_TRUE : m_device(addressof(m)), owns(false) {}

    unique_lock(mutex_type& m, try_to_lock_t) : m_device(addressof(m)), owns(m_device->try_lock()) {}

    unique_lock(mutex_type& m, adopt_lock_t) SROOK_NOEXCEPT_TRUE : m_device(addressof(m)), owns(true) {}

    ~unique_lock()
    {
        if (owns) unlock();
    }

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    unique_lock(unique_lock&& u) SROOK_NOEXCEPT_TRUE : m_device(u.m_device), owns(u.owns)
    {
        u.m_device = 0;
        u.owns = false;
    }
#    endif

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    unique_lock& operator=(unique_lock&& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        unique_lock(srook::move(u)).swap(*this);
        u.m_device = 0;
        u.owns = false;

        return *this;
    }
#    endif

    void swap(unique_lock& u) SROOK_NOEXCEPT_TRUE
    {
        std::swap(m_device, u.m_device);
        std::swap(owns, u.owns);
    }

    mutex_type* release() SROOK_NOEXCEPT_TRUE
    {
        mutex_type* ret = m_device;
        m_device = 0;
        owns = false;
        return ret;
    }

    bool owns_lock() const SROOK_NOEXCEPT_TRUE { return owns; }

    SROOK_EXPLICIT operator bool() const SROOK_NOEXCEPT_TRUE { return owns_lock(); }

    mutex_type* mutex() const SROOK_NOEXCEPT_TRUE { return m_device; }

#    define DEF_MEMFN(CHLIB, SYSLIB)                                                                                             \
        template <class Clock, class Duration>                                                                                   \
        unique_lock(mutex_type& m, const CHLIB::chrono::time_point<Clock, Duration>& time)                                       \
            : m_device(addressof(m)), owns(m_device->try_lock_until(time))                                                       \
        {                                                                                                                        \
        }                                                                                                                        \
        template <class Rep, class Period>                                                                                       \
        unique_lock(mutex_type& m, const CHLIB::chrono::duration<Rep, Period>& time)                                             \
            : m_device(addressof(m)), owns(m_device->try_lock_for(time))                                                         \
        {                                                                                                                        \
        }                                                                                                                        \
        void lock()                                                                                                              \
        {                                                                                                                        \
            if (!m_device) {                                                                                                     \
                SYSLIB::error_code ec(static_cast<int>(SYSLIB::errc::operation_not_permitted), SYSLIB::system_category());       \
                throw SYSLIB::system_error(srook::move(ec), "operation not permitted");                                          \
            } else if (owns) {                                                                                                   \
                SYSLIB::error_code ec(static_cast<int>(SYSLIB::errc::resource_deadlock_would_occur), SYSLIB::system_category()); \
                throw SYSLIB::system_error(srook::move(ec), "resource deadlock would occur");                                    \
            } else {                                                                                                             \
                m_device->lock();                                                                                                \
                owns = true;                                                                                                     \
            }                                                                                                                    \
        }                                                                                                                        \
        bool try_lock()                                                                                                          \
        {                                                                                                                        \
            if (!m_device) {                                                                                                     \
                SYSLIB::error_code ec(static_cast<int>(SYSLIB::errc::operation_not_permitted), SYSLIB::system_category());       \
                throw SYSLIB::system_error(srook::move(ec), "operation not permitted");                                          \
            } else if (owns) {                                                                                                   \
                SYSLIB::error_code ec(static_cast<int>(SYSLIB::errc::resource_deadlock_would_occur), SYSLIB::system_category()); \
                throw SYSLIB::system_error(srook::move(ec), "resource deadlock would occur");                                    \
            } else {                                                                                                             \
                owns = m_device->try_lock();                                                                                     \
                return owns;                                                                                                     \
            }                                                                                                                    \
        }                                                                                                                        \
        template <class Clock, typename Duration>                                                                                \
        bool try_lock_until(const CHLIB::chrono::time_point<Clock, Duration>& time)                                              \
        {                                                                                                                        \
            if (!m_device) {                                                                                                     \
                SYSLIB::error_code ec(static_cast<int>(SYSLIB::errc::operation_not_permitted), SYSLIB::system_category());       \
                throw SYSLIB::system_error(srook::move(ec), "operation not permitted");                                          \
            } else if (owns) {                                                                                                   \
                SYSLIB::error_code ec(static_cast<int>(SYSLIB::errc::resource_deadlock_would_occur), SYSLIB::system_category()); \
                throw SYSLIB::system_error(srook::move(ec), "resource deadlock would occur");                                    \
            } else {                                                                                                             \
                owns = m_device->try_lock_until(time);                                                                           \
                return owns;                                                                                                     \
            }                                                                                                                    \
        }                                                                                                                        \
        template <class Rep, class Period>                                                                                       \
        bool try_lock_for(const CHLIB::chrono::duration<Rep, Period>& time)                                                      \
        {                                                                                                                        \
            if (!m_device) {                                                                                                     \
                SYSLIB::error_code ec(static_cast<int>(SYSLIB::errc::operation_not_permitted), SYSLIB::system_category());       \
                throw SYSLIB::system_error(srook::move(ec), "operation not permitted");                                          \
            } else if (owns) {                                                                                                   \
                SYSLIB::error_code ec(static_cast<int>(SYSLIB::errc::resource_deadlock_would_occur), SYSLIB::system_category()); \
                throw SYSLIB::system_error(srook::move(ec), "resource deadlock would occur");                                    \
            } else {                                                                                                             \
                owns = m_device->try_lock_for(time);                                                                             \
                return owns;                                                                                                     \
            }                                                                                                                    \
        }                                                                                                                        \
        void unlock()                                                                                                            \
        {                                                                                                                        \
            if (!owns) {                                                                                                         \
                SYSLIB::error_code ec(static_cast<int>(SYSLIB::errc::operation_not_permitted), SYSLIB::system_category());       \
                throw SYSLIB::system_error(srook::move(ec), "operation not permitted");                                          \
            } else if (m_device) {                                                                                               \
                m_device->unlock();                                                                                              \
                owns = false;                                                                                                    \
            }                                                                                                                    \
        }

#    if SROOK_HAS_INCLUDE(<chrono>) && SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS
    DEF_MEMFN(std, std)
#    elif (SROOK_HAS_INCLUDE(<boost/chrono.hpp>) || SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)) && !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
    DEF_MEMFN(boost, boost::system)
#    endif
#    undef DEF_MEMFN
private:
    mutex_type* m_device;
    bool owns;

    friend inline void swap(unique_lock& lhs, unique_lock& rhs) SROOK_NOEXCEPT_TRUE
    {
        lhs.swap(rhs);
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace thread

using thread::unique_lock;

} // namespace srook

#    else
#        error This environment is not supported.
#    endif

#endif
