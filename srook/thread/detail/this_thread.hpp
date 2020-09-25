// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_THREAD_DETAIL_THIS_THREAD_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_THIS_THREAD_HPP

#include <srook/thread/detail/thread_base.hpp>
#include <srook/mutex/mutexes/mutex.hpp>
#include <srook/mutex/guards/unique_lock.hpp>
#include <srook/condition_variable.hpp>

namespace srook {
namespace threading {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

thread::id get_id() SROOK_NOEXCEPT_TRUE
{
#ifdef __GLIBC__
	if (ext::thread_active_p()) return thread::id(1);
#endif
	return thread::id(thread_get_current_id());
}

inline SROOK_ATTRIBUTE_INLINE_VISIBILITY 
void yield() SROOK_NOEXCEPT_TRUE
{
	thread_yield();
}

SROOK_ATTRIBUTE_FUNCTION_VIS_DEFAULT
void sleep_for(mutexes::includes::chrono::nanoseconds ns)
{
	if (ns > mutexes::includes::chrono::nanoseconds::zero()) {
		thread_sleep_for(ns);
	}
}

template <class Rep, class Period>
void sleep_for(const mutexes::includes::chrono::duration<Rep, Period>& d)
{
	using namespace mutexes::includes::chrono;
	if (d > duration<Rep, Period>::zero()) {
		SROOK_CONSTEXPR_OR_CONST duration<long double> max = nanoseconds::max();
		nanoseconds ns;
		if (d < max) {
			ns = duration_cast<nanoseconds>(d);
			if (ns < d) ++ns;
		} else {
			ns = nanoseconds::max();
		}
		sleep_for(ns);
	}
}

template <class Clock, class Duration>
void sleep_until(const mutexes::includes::chrono::time_point<Clock, Duration>& t)
{
	using namespace mutexes::includes::chrono;

	mutex m;
	condition_variable cv;
	unique_lock<mutex> lk(m);
	while (Clock::now() < t) cv.wait_until(lk, t);
}

template <class Duration>
inline SROOK_ATTRIBUTE_INLINE_VISIBILITY
void sleep_until(const mutexes::includes::chrono::time_point<mutexes::includes::chrono::steady_clock, Duration>& t)
{
	sleep_for(t - mutexes::includes::chrono::steady_clock::now());
}

} // namespace detail	
SROOK_INLINE_NAMESPACE_END
} // namespace thread
} // namespace srook

#endif
