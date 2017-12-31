// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MUTEX_TIMED_MUTEX_HPP
#define INCLUDED_SROOK_MUTEX_TIMED_MUTEX_HPP

#include <srook/mutex/mutexes/detail/timed_mutex_base.hpp>
#include <srook/mutex/mutexes/mutex.hpp>
#include <srook/type_traits/is_nothrow_default_constructible.hpp>
#include <srook/type_traits/library_concepts/is_mutex.hpp>
#if !SROOK_PTHREAD_TIMEOUTS_SUPPORT
#    include <cassert>
#    include <srook/condition_variable.hpp>
#    include <srook/mutex/guards.hpp>
#endif

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

#if !SROOK_PTHREAD_TIMEOUTS_SUPPORT
#    if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT && !SROOK_CPP_LAMBDAS
#        define LOCKED_CHECK LockedCheck(this)
#    else
#        define LOCKED_CHECK [this] { return !locked; }
#    endif

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex"))
    timed_mutex : private mutex_base {
    mutex m;
    condition_variable cv;
    bool locked
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = false
#    endif
        ;
public:
    typedef native_type* native_handle_type;

    SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE
    SROOK_CONSTEXPR timed_mutex() SROOK_NOEXCEPT_TRUE
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        SROOK_DEFAULT
#    else
        : m(),
          cv(),
          locked(false)
    {}
#    endif

        ~timed_mutex()
    {
        assert(!locked);
    }

    timed_mutex(const timed_mutex&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE

    timed_mutex& operator=(const timed_mutex&) SROOK_EQ_DELETE

    void lock()
    SROOK_THREAD_SAFETY_ANNOTATION(acquire_capability())
    {
        unique_lock<mutex> lk(m);
        cv.wait(lk, LOCKED_CHECK);
        locked = true;
    }

    bool try_lock() SROOK_NOEXCEPT_TRUE
    SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        unique_lock<mutex> lk(m);
        if (locked) return false;
        locked = true;
        return locked;
    }

    template <class Rep, class Period>
    bool try_lock_for(const includes::chrono::duration<Rep, Period>& rtime)
    SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        unique_lock<mutex> lk(m);
        if (!cv.wait_for(lk, rtime, LOCKED_CHECK)) return false;
        return locked = true;
    }

    template <class Clock, class Duration>
    bool try_lock_until(const includes::chrono::time_point<Clock, Duration>& atime)
    SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        unique_lock<mutex> lk(m);
        if (!cv.wait_until(lk, atime, LOCKED_CHECK)) return false;
        return locked = true;
    }

    void unlock() SROOK_NOEXCEPT_TRUE
    SROOK_THREAD_SAFETY_ANNOTATION(release_capability())
    {
        lock_guard<mutex> lk(m);
        assert(locked);
        locked = false;
        cv.notify_one();
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    native_handle_type native_handle() SROOK_NOEXCEPT_TRUE
    {
        return m.native_handle();
    }

#    if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT && !SROOK_CPP_LAMBDAS
private:
    struct SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT LockedCheck {
        SROOK_ATTRIBUTE_INLINE_VISIBILITY
        explicit LockedCheck(timed_mutex* this_ptr) SROOK_NOEXCEPT_TRUE : this_ptr_(this_ptr) {}
        SROOK_ATTRIBUTE_INLINE_VISIBILITY
        const bool operator()() const SROOK_NOEXCEPT_TRUE { return !this_ptr_->locked; }

    private:
        const timed_mutex* const this_ptr_;
    };
#    endif
};

#    undef LOCKED_CHECK
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_STATIC_ASSERT(is_mutex<mutex>::value&& is_nothrow_default_constructible<mutex>::value,
                    "the default constructor for srook::mutex must be nothrow");
#    endif

#else

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex"))
    timed_mutex : private mutex_base,
                  public timed_mutex_base<timed_mutex> {
public:
    typedef native_type* native_handle_type;

    timed_mutex() SROOK_DEFAULT
    ~timed_mutex() SROOK_DEFAULT

    void lock()
    SROOK_THREAD_SAFETY_ANNOTATION(acquire_capability())
    {
        const int e = threading::detail::mutex_lock(&m);
        if (e) includes::throw_system_err(e);
    }

    bool try_lock() SROOK_NOEXCEPT_TRUE
    SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        return threading::detail::mutex_trylock(&m);
    }

    template <class Rep, class Period>
    bool try_lock_for(const includes::chrono::duration<Rep, Period>& rtime)
    SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        return invoke_try_lock_for(rtime);
    }

    template <class Clock, class Duration>
    bool try_lock_until(const includes::chrono::time_point<Clock, Duration>& atime)
    SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        return invoke_try_lock_until(atime);
    }

    void unlock()
    SROOK_THREAD_SAFETY_ANNOTATION(release_capability())
    {
        threading::detail::mutex_unlock(&m);
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    native_handle_type native_handle() SROOK_NOEXCEPT_TRUE
    {
        return &m;
    }

private:
    friend class timed_mutex_base<timed_mutex>;
    bool timedlock(const threading::detail::thread_time_type& ts)
    SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        return !threading::detail::mutex_timedlock(&m, &ts);
    }
};

#endif

SROOK_INLINE_NAMESPACE_END

} // namespace mutexes

using mutexes::timed_mutex;

} // namespace srook

#endif
