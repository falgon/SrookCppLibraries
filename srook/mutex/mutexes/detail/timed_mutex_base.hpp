// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MUTEX_MUTEXES_DETAIL_TIMED_MUTEX_BASE_HPP
#define INCLUDED_SROOK_MUTEX_MUTEXES_DETAIL_TIMED_MUTEX_BASE_HPP

#include <srook/mutex/includes/lib.hpp>

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

template <class Derived>
class timed_mutex_base {
protected:
	typedef includes::chrono::high_resolution_clock clock_type;

	template <class Rep, class Period>
	bool invoke_try_lock_for(const includes::chrono::duration<Rep, Period>& rtime)
	{
		using namespace includes::chrono;
		steady_clock::duration rt = duration_cast<steady_clock::duration>(rtime);
		if (includes::ratio_greater<steady_clock::period, Period>()) ++rt;
		return invoke_try_lock_until(steady_clock::now() + rt);
	}

	template <class Duration>
	bool invoke_try_lock_until(const includes::chrono::time_point<clock_type, Duration>& atime)
	{
		using namespace includes::chrono;

		const time_point<clock_type, seconds> s = time_point_cast<seconds>(atime);
		nanoseconds ns = duration_cast<nanoseconds>(atime - s);

		threading::detail::thread_time_type ts = {
			static_cast<std::time_t>(s.time_since_epoch().count()),
			static_cast<long>(ns.count())
		};
		return static_cast<Derived*>(this)->timedlock(ts);
	}

	template <class Clock, class Duration>
	bool invoke_try_lock_until(const includes::chrono::time_point<Clock, Duration>& atime)
	{
		return invoke_try_lock_until(clock_type::now() + (atime - Clock::now()));
	}
};
SROOK_INLINE_NAMESPACE_END
} // namespace mutexes
} // namespace srook

#endif
