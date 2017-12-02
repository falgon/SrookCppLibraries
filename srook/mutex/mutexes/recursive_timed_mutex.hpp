// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MUTEX_RECURSIVE_TIMED_MUTEX_HPP
#define INCLUDED_SROOK_MUTEX_RECURSIVE_TIMED_MUTEX_HPP

#include <srook/mutex/mutexes/mutex.hpp>
#include <srook/type_traits/is_nothrow_default_constructible.hpp>
#include <srook/type_traits/library_concepts/is_mutex.hpp>
#include <srook/thread.hpp>
#if !SROOK_PTHREAD_TIMEOUTS_SUPPORT
#    include <cassert>
#    include <srook/condition_variable.hpp>
#    include <srook/mutex/guards.hpp>
#endif

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

#if !SROOK_PTHREAD_TIMEOUTS_SUPPORT

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex"))
    recursive_timed_mutex : private mutex_base {
    mutex m;
    condition_variable cv;
	thread::id owner;
    unsigned count
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = 0
#    endif
        ;
	struct Lockable_ {
		explicit Lockable_(recursive_timed_mutex* p, thread::id i) SROOK_NOEXCEPT_TRUE : rm(p), caller(i) {}
		SROOK_CONSTEXPR_OR_CONST bool operator()() const SROOK_NOEXCEPT_TRUE 
		{
			return rm->count == 0 || rm->owner == caller;
		}

		const recursive_timed_mutex* rm;
		thread::id caller;
	};
public:
    typedef native_type* native_handle_type;

    SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE
    recursive_timed_mutex() SROOK_NOEXCEPT_TRUE
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        SROOK_DEFAULT
#    else
        : m(),
          cv(),
          count(0)
    {}
#    endif

    ~recursive_timed_mutex()
    {
        assert(!count);
    }

    recursive_timed_mutex(const recursive_timed_mutex&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE

    recursive_timed_mutex& operator=(const recursive_timed_mutex&) SROOK_EQ_DELETE

    void lock() 
	SROOK_THREAD_SAFETY_ANNOTATION(acquire_capability())
    {
		const thread::id id = this_thread::get_id();
		const Lockable_ lockable(this, id);
		unique_lock<mutex> lk(m);
		cv.wait(lk, lockable);
		if (count == -1u) includes::throw_system_err(EAGAIN);
		owner = id;
		++count;
    }

    bool try_lock() SROOK_NOEXCEPT_TRUE 
	SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
		const thread::id id = this_thread::get_id();
		const Lockable_ lockable(this, id);
		lock_guard<mutex> lk(m);
		if (!lockable()) return false;
		if (count == -1u) return false;
		owner = id;
		++count;
		return true;
    }

    template <class Rep, class Period>
    bool try_lock_for(const includes::chrono::duration<Rep, Period>& rtime) 
    SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
		const thread::id id = this_thread::get_id();
		const Lockable_ lockable(this, id);
		unique_lock<mutex> lk(m);
		if (!cv.wait_for(lk, rtime, lockable)) return false;
		if (count == -1u) return false;
		owner = id;
		++count;
		return true;
    }

    template <class Clock, class Duration>
    bool try_lock_until(const includes::chrono::time_point<Clock, Duration>& atime)
    SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
		const thread::id id = this_thread::get_id();
		const Lockable_ lockable(this, id);
		unique_lock<mutex> lk(m);
		if (!cv.wait_until(lk, atime, lockable)) return false;
		if (count == -1u) return false;
		owner = id;
		++count;
		return true;
    }

    void unlock() SROOK_NOEXCEPT_TRUE 
    SROOK_THREAD_SAFETY_ANNOTATION(release_capability())
    {
        lock_guard<mutex> lk(m);
        assert(owner == this_thread::get_id());
		assert(count > 0);
		if (--count == 0) {
			owner = 
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
			{}
#else
			thread::id()
#endif
				;
			cv.notify_one();
		}
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY 
    native_handle_type native_handle() SROOK_NOEXCEPT_TRUE
    {
        return m.native_handle();
    }
};

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_STATIC_ASSERT(is_mutex<mutex>::value&& is_nothrow_default_constructible<mutex>::value,
                    "the default constructor for srook::mutex must be nothrow");
#    endif

#else

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex"))
    recursive_timed_mutex : private recursive_mutex_base,
                  public timed_mutex_base<recursive_timed_mutex> {
public:
    typedef native_type* native_handle_type;

    recursive_timed_mutex() SROOK_DEFAULT
    ~recursive_timed_mutex() SROOK_DEFAULT

    void lock()
	SROOK_THREAD_SAFETY_ANNOTATION(acquire_capability())
    {
        const int e = threading::detail::recursive_mutex_lock(&m);
        if (e) includes::throw_system_err(e);
    }

    bool try_lock() SROOK_NOEXCEPT_TRUE
	SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        return threading::detail::recursive_mutex_trylock(&m);
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
        threading::detail::recursive_mutex_unlock(&m);
	}

    SROOK_ATTRIBUTE_INLINE_VISIBILITY 
	native_handle_type native_handle() SROOK_NOEXCEPT_TRUE
	{
		return &m;
	}
private:
    friend class recursive_mutex_base;
    friend class timed_mutex_base<recursive_timed_mutex>;
    bool timedlock(const threading::detail::thread_time_type& ts)
	SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        return !threading::detail::mutex_timedlock(&m, &ts);
    }
};

#endif

SROOK_INLINE_NAMESPACE_END

} // namespace mutexes

using mutexes::recursive_timed_mutex;

} // namespace srook

#endif
