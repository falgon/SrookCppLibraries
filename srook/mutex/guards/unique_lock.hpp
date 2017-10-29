// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MUTEX_GUARDS_UNIQUE_LOCK_HPP
#define INCLUDED_SROOK_MUTEX_GUARDS_UNIQUE_LOCK_HPP

#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/feature/explicit.hpp>
#include <srook/config/feature/exception.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/static_assert.hpp>
#include <srook/config/libraries/nullptr.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/user_config.hpp>
#include <srook/memory/addressof.hpp>
#include <srook/mutex/detail/lock_tags.hpp>
#include <srook/type_traits/library_concepts/is_mutex.hpp>
#include <srook/utility/move.hpp>
#include <srook/utility/noncopyable.hpp>

#if (SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>) || SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)) && (SROOK_HAS_INCLUDE(<system_error>) || SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>))

#    if SROOK_HAS_INCLUDE(<chrono>) && SROOK_HAS_INCLUDE(<system_error>) && SROOK_HAS_INCLUDE(<mutex>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#        include <chrono>
#        include <mutex>
#        include <system_error>
#    elif SROOK_HAS_INCLUDE(<boost/chrono.hpp>) && SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
#        include <boost/chrono.hpp>
#        include <boost/system/system_error.hpp>
#        if SROOK_HAS_INCLUDE(<boost/thread.hpp>)
#            include <boost/thread.hpp>
#        endif
#    elif SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>) && SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
#        include <boost/chrono/include.hpp>
#        include <boost/system/system_error.hpp>
#        if SROOK_HAS_INCLUDE(<boost/thread.hpp>)
#            include <boost/thread.hpp>
#        endif
#    endif

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

template <class Mutex>
class unique_lock
#    if !defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE) && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
    : private noncopyable<unique_lock<Mutex> >
#    endif
{
public:
    typedef Mutex mutex_type;
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_STATIC_ASSERT(is_mutex<Mutex>::value, "The template argument must be Mutex");
#    endif
    unique_lock() SROOK_NOEXCEPT_TRUE : m_device(SROOK_NULLPTR), owns(false) {}

    SROOK_EXPLICIT unique_lock(mutex_type& m) : m_device(addressof(m)), owns(false)
    {
        lock();
        owns = true;
    }

#    define DEF_CONSTRUCT_LOCK_T(LIB)\
    unique_lock(mutex_type& m, LIB::defer_lock_t) SROOK_NOEXCEPT_TRUE : m_device(addressof(m)), owns(false) {}\
    unique_lock(mutex_type& m, LIB::try_to_lock_t) : m_device(addressof(m)), owns(m_device->try_lock()) {}\
    unique_lock(mutex_type& m, LIB::adopt_lock_t) SROOK_NOEXCEPT_TRUE : m_device(addressof(m)), owns(true) {}

    DEF_CONSTRUCT_LOCK_T(srook)
#        if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_HAS_INCLUDE(<mutex>)
    DEF_CONSTRUCT_LOCK_T(std)
#        elif !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && SROOK_HAS_INCLUDE(<boost/thread.hpp>)
    DEF_CONSTRUCT_LOCK_T(boost)
#        endif
#    undef DEF_CONSTRUCT_LOCK_T

    ~unique_lock()
    {
        if (owns) unlock();
    }

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    unique_lock(unique_lock&& u) SROOK_NOEXCEPT_TRUE : m_device(u.m_device), owns(u.owns)
    {
        u.m_device = SROOK_NULLPTR;
        u.owns = false;
    }

    unique_lock& operator=(unique_lock&& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        unique_lock(srook::move(u)).swap(*this);
        u.m_device = SROOK_NULLPTR;
        u.owns = false;

        return *this;
    }

    unique_lock(std::unique_lock<mutex_type>&& u) SROOK_NOEXCEPT_TRUE : m_device(u.mutex()), owns(u.owns_lock())
    {
        u.release();
    }

    unique_lock& operator=(std::unique_lock<mutex_type>&& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        m_device = u.mutex();
        owns = u.owns_lock();
        u.release();

        return *this;
    }

    // boost::unique_lock is not supported
    // because when valid this block, the environment should able to use std::unique_lock.
#    elif SROOK_HAS_INCLUDE(<boost/thread.hpp>) && defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE)
    // Deprecated because there is not the semantics of rvalue reference in C++03.
    // Behaves similarly to auto_ptr

    SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
    unique_lock(unique_lock& u) SROOK_NOEXCEPT_TRUE : m_device(u.m_device), owns(u.owns)
    {
        u.m_device = SROOK_NULLPTR;
        u.owns = false;
    }

    SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
    unique_lock& operator=(unique_lock& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        m_device = u.m_device;
        owns = u.owns;
        u.m_device = SROOK_NULLPTR;
        u.owns = false;
    }

#        if SROOK_HAS_INCLUDE(<boost/thread.hpp>)
    SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
    unique_lock(boost::unique_lock<mutex_type>& u) SROOK_NOEXCEPT_TRUE : m_device(u.mutex()), owns(u.owns_lock())
    {
        u.release();
    }

    SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
    unique_lock& operator=(boost::unique_lock<mutex_type>& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        m_device = u.mutex();
        owns = u.owns_lock();
        u.release();

        return *this;
    }
#        endif
#    elif !defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE)

    unique_lock(const utility::cxx03::move_tag<unique_lock>& u) SROOK_NOEXCEPT_TRUE : m_device(u.get().m_device), owns(u.get().owns)
    {
        u.get().m_device = SROOK_NULLPTR;
        u.get().owns = false;
    }

    unique_lock& operator=(const utility::cxx03::move_tag<unique_lock>& u) SROOK_NOEXCEPT_TRUE
    {
        if (owns) unlock();
        unique_lock(srook::move(u)).swap(*this);
        u.get().m_device = SROOK_NULLPTR;
        u.get().owns = false;

        return *this;
    }

#        if SROOK_HAS_INCLUDE(<boost/thread.hpp>)
	unique_lock(const utility::cxx03::move_tag<boost::unique_lock<mutex_type> >& u) SROOK_NOEXCEPT_TRUE 
		: m_device(u.get().mutex()), owns(u.get().owns_lock())
	{
		u.get().release();
	}

	unique_lock& operator=(const utility::cxx03::move_tag<boost::unique_lock<mutex_type> >& u) SROOK_NOEXCEPT_TRUE
	{
		if (owns) unlock();
		m_device = u.get().mutex();
		owns = u.get().owns_lock();
		u.get().release();

		return *this;
	}

#        endif
#    endif

    void swap(unique_lock& u) SROOK_NOEXCEPT_TRUE
    {
        std::swap(m_device, u.m_device);
        std::swap(owns, u.owns);
    }

    mutex_type* release() SROOK_NOEXCEPT_TRUE
    {
        mutex_type* ret = m_device;
        m_device = SROOK_NULLPTR;
        owns = false;
        return ret;
    }

    bool owns_lock() const SROOK_NOEXCEPT_TRUE { return owns; }

    SROOK_EXPLICIT operator bool() const SROOK_NOEXCEPT_TRUE { return owns_lock(); }

    mutex_type* mutex() const SROOK_NOEXCEPT_TRUE { return m_device; }

#    define THROW_SYSTEM_ERR(SYSLIB, ERRC) \
        SROOK_THROW(SYSLIB::system_error(        \
            SYSLIB::error_code(static_cast<int>(SYSLIB::errc::ERRC), SYSLIB::system_category()), #ERRC))

#    define DEF_MEMFN(CHLIB, SYSLIB)                                                       \
        template <class Clock, class Duration>                                             \
        unique_lock(mutex_type& m, const CHLIB::chrono::time_point<Clock, Duration>& time) \
            : m_device(addressof(m)), owns(m_device->try_lock_until(time))                 \
        {                                                                                  \
        }                                                                                  \
        template <class Rep, class Period>                                                 \
        unique_lock(mutex_type& m, const CHLIB::chrono::duration<Rep, Period>& time)       \
            : m_device(addressof(m)), owns(m_device->try_lock_for(time))                   \
        {                                                                                  \
        }                                                                                  \
        void lock()                                                                        \
        {                                                                                  \
            if (!m_device) {                                                               \
                THROW_SYSTEM_ERR(SYSLIB, operation_not_permitted);                         \
            } else if (owns) {                                                             \
                THROW_SYSTEM_ERR(SYSLIB, resource_deadlock_would_occur);                   \
            } else {                                                                       \
                m_device->lock();                                                          \
                owns = true;                                                               \
            }                                                                              \
        }                                                                                  \
        bool try_lock()                                                                    \
        {                                                                                  \
            if (!m_device) {                                                               \
                THROW_SYSTEM_ERR(SYSLIB, operation_not_permitted);                         \
            } else if (owns) {                                                             \
                THROW_SYSTEM_ERR(SYSLIB, resource_deadlock_would_occur);                   \
            } else {                                                                       \
                owns = m_device->try_lock();                                               \
                return owns;                                                               \
            }                                                                              \
        }                                                                                  \
        template <class Clock, typename Duration>                                          \
        bool try_lock_until(const CHLIB::chrono::time_point<Clock, Duration>& time)        \
        {                                                                                  \
            if (!m_device) {                                                               \
                THROW_SYSTEM_ERR(SYSLIB, operation_not_permitted);                         \
            } else if (owns) {                                                             \
                THROW_SYSTEM_ERR(SYSLIB, resource_deadlock_would_occur);                   \
            } else {                                                                       \
                owns = m_device->try_lock_until(time);                                     \
                return owns;                                                               \
            }                                                                              \
        }                                                                                  \
        template <class Rep, class Period>                                                 \
        bool try_lock_for(const CHLIB::chrono::duration<Rep, Period>& time)                \
        {                                                                                  \
            if (!m_device) {                                                               \
                THROW_SYSTEM_ERR(SYSLIB, operation_not_permitted);                         \
            } else if (owns) {                                                             \
                THROW_SYSTEM_ERR(SYSLIB, resource_deadlock_would_occur);                   \
            } else {                                                                       \
                owns = m_device->try_lock_for(time);                                       \
                return owns;                                                               \
            }                                                                              \
        }                                                                                  \
        void unlock()                                                                      \
        {                                                                                  \
            if (!owns) {                                                                   \
                THROW_SYSTEM_ERR(SYSLIB, operation_not_permitted);                         \
            } else if (m_device) {                                                         \
                m_device->unlock();                                                        \
                owns = false;                                                              \
            }                                                                              \
        }

#    if SROOK_HAS_INCLUDE(<chrono>) && SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS
    DEF_MEMFN(std, std)
#    elif (SROOK_HAS_INCLUDE(<boost/chrono.hpp>) || SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)) && !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
    DEF_MEMFN(boost, boost::system)
#    endif
#    undef DEF_MEMFN
#    undef THROW_SYSTEM_ERR
private:
    mutex_type* m_device;
    bool owns;

    friend inline void swap(unique_lock& lhs, unique_lock& rhs) SROOK_NOEXCEPT_TRUE
    {
        lhs.swap(rhs);
    }
};

#    if (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT) && SROOK_CPP_DEDUCTION_GUIDES

template <class M>
unique_lock(unique_lock<M>) -> unique_lock<M>;

#    endif

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes

using mutexes::unique_lock;

} // namespace srook

#    else
#        error This environment is not supported.
#    endif

#endif
