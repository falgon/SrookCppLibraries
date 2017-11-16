// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MUTEX_CV_CONDITION_VARIABLE_HPP
#define INCLUDED_SROOK_MUTEX_CV_CONDITION_VARIABLE_HPP
#include <srook/config/cpp_predefined.hpp>

#if (SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>) || SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)) && (SROOK_HAS_INCLUDE(<system_error>) || SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>))
#    include <srook/chrono/ceil.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/config/noexcept_detection.hpp>
#    include <srook/mutex/guards/unique_lock.hpp>
#    include <srook/mutex/mutexes/mutex.hpp>
#    include <srook/thread/detail/support.hpp>
#    include <srook/utility/noncopyable.hpp>
#    include <srook/type_traits/is_callable.hpp>
#    include <srook/limits/numeric_limits.hpp>
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_HAS_INCLUDE(<chrono>) && SROOK_HAS_INCLUDE(<system_error>)
#        define CONDVAR_INLINE_INIT = SROOK_COND_VAR_INITIALIZER
#        include <chrono>
#        include <system_error>
#        define STD_INCLUDED 1
#    elif !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) &&\
			(SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>)) &&\
			SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
#        define CONDVAR_INLINE_INIT
#        include <boost/system/system_error.hpp>
#        if SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#            include <boost/chrono.hpp>
#        else
#            include <boost/chrono/include.hpp>
#        endif
#        define BOOST_INCLUDED 1
#    endif

namespace srook {
namespace cv {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

namespace included_type =
#ifdef STD_INCLUDED
#undef STD_INCLUDED
std
#elif BOOST_INCLUDED
#undef BOOST_INCLUDED
boost
#endif
;

} // namespace detail

SROOK_STRONG_ENUM_BEGIN(cv_status) {
	no_timeout,
	timeout
};
SROOK_STRONG_ENUM_EPILOG(cv_status)

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT condition_variable : private noncopyable<condition_variable> {
    threading::detail::cond_var_type cv CONDVAR_INLINE_INIT;

public:
    SROOK_ATTRIBUTE_INLINE_VISIBILITY SROOK_CONSTEXPR condition_variable() SROOK_NOEXCEPT_TRUE
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        SROOK_DEFAULT
#    else
    {
        cv = (threading::detail::cond_var_type)SROOK_COND_VAR_INITIALIZER;
    }
#    endif
    ~condition_variable()
    {
        threading::detail::condvar_destroy(&cv);
    }

    void notify_one() SROOK_NOEXCEPT_TRUE
    {
        threading::detail::condvar_signal(&cv);
    }

    void notify_all() SROOK_NOEXCEPT_TRUE
    {
        threading::detail::condvar_broadcast(&cv);
    }

#    define THROW_SYSTEM_ERR(SYSLIB, ERRC, MES) \
        SROOK_THROW(                            \
            SYSLIB::system_error(               \
                SYSLIB::error_code(static_cast<int>(SYSLIB::errc::ERRC), SYSLIB::system_category()), #MES))
#    define THROW_SYSTEM_ERR_CODE(SYSLIB, ERRC, MES) \
        SROOK_THROW(                                 \
            SYSLIB::system_error(                    \
                SYSLIB::error_code(ERRC, SYSLIB::system_category()), #MES))

    void wait(unique_lock<mutex>& lk)
    {
        if (!lk.owns_lock())
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
            THROW_SYSTEM_ERR_CODE(std, EPERM, condition_variable::wait: mutex not locked)
#    else
            THROW_SYSTEM_ERR_CODE(boost::system, EPERM, condition_variable::wait: mutex not locked)
#    endif
                ;
		const int ec = threading::detail::condvar_wait(&cv, lk.mutex()->native_handle());
		if(ec) 
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
			THROW_SYSTEM_ERR_CODE(std, ec, condition_variable wait failed)
#    else
            THROW_SYSTEM_ERR_CODE(boost::system, ec, condition_variable wait failed)
#    endif
			;
    }

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#        define PRED_TYPE Pred
#    else
#        define PRED_TYPE const Pred&
#    endif

	template <class Pred>
	SROOK_ATTRIBUTE_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS_DEFAULT
	void wait(unique_lock<mutex>& lk, PRED_TYPE pred)
	{
		SROOK_STATIC_ASSERT(is_callable<Pred>::value, "Predicate must be callable");
		while(!pred()) wait(lk);
	}

	template <class Clock, class Duration>
	SROOK_ATTRIBUTE_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS_DEFAULT
	cv_status wait_until(unique_lock<mutex>& lk, const detail::included_type::chrono::time_point<Clock, Duration>& t)
	{
		using namespace detail::included_type::chrono;
		wait_for(lk, t - Clock::now());
		return Clock::now() < t ? cv_status::no_timeout : cv_status::timeout;
	}

	template <class Clock, class Duration, class Pred>
	SROOK_ATTRIBUTE_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS_DEFAULT
	bool wait_until(unique_lock<mutex>& lk, const detail::included_type::chrono::time_point<Clock, Duration>& t, PRED_TYPE pred)
	{
		SROOK_STATIC_ASSERT(is_callable<Pred>::value, "Predicate must be callable");
		while(!pred()) {
			if (wait_until(lk, t) == cv_status::timeout) return pred();
		}
		return true;
	}
#    undef PRED_TYPE

	template <class Rep, class Period>
	SROOK_ATTRIBUTE_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS_DEFAULT
	cv_status wait_for(unique_lock<mutex>& lk, const detail::included_type::chrono::duration<Rep, Period>& d)
	{
		using namespace detail::included_type::chrono;
		
		if(d <= d.zero()) return cv_status::timeout;
		typedef time_point<system_clock, duration<long double, detail::included_type::nano> > sys_tpf;
		typedef time_point<system_clock, nanoseconds> sys_tpi;
		const sys_tpf max = sys_tpi::max();

		steady_clock::time_point c_now = steady_clock::now();
		system_clock::time_point s_now = system_clock::now();

		if (max - d > s_now) timed_wait(lk, s_now + srook::chrono::ceil<nanoseconds>(d));
		else timed_wait(lk, sys_tpi::max());

		return steady_clock::now() - c_now < d ? cv_status::no_timeout : cv_status::timeout;
	}

	template <class Rep, class Period, class Predicate>
	inline bool wait_for(unique_lock<mutex>& lk, const detail::included_type::chrono::duration<Rep, Period>& d, Predicate pred)
	{
		return wait_until(lk, detail::included_type::chrono::steady_clock::now() + d, 
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
				srook::move(pred)
#    else
				pred
#    endif
			);
	}
private:
	void timed_wait(unique_lock<mutex>& lk, detail::included_type::chrono::time_point<detail::included_type::chrono::system_clock, detail::included_type::chrono::nanoseconds> tp)
	{
		using namespace detail::included_type::chrono;
		if (!lk.owns_lock()) 
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
			THROW_SYSTEM_ERR_CODE(std, EPERM, condition_variable::timed wait: mutex not locked)
#    else
		    THROW_SYSTEM_ERR_CODE(boost::system, EPERM, condition_variable::timed wait: mutex not locked)
#    endif
				;

		nanoseconds d = tp.time_since_epoch();
		if (d > nanoseconds(0x59682F000000E941)) d = nanoseconds(0x59682F000000E941);

		threading::detail::thread_time_type ts;
		seconds s = duration_cast<seconds>(d);

		typedef
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
			decltype(ts.tv_sec)
#    else
			std::time_t
#    endif
			ts_sec;

		SROOK_CONSTEXPR_OR_CONST ts_sec ts_sec_max = numeric_limits<ts_sec>::max();

		if (s.count() < ts_sec_max) {
			ts.tv_sec = static_cast<ts_sec>(s.count());
			ts.tv_nsec = static_cast<
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
				decltype(ts.tv_nsec)
#    else
				long int
#    endif
			>((d - s).count());
		} else {
			ts.tv_sec = ts_sec_max;
			ts.tv_nsec = detail::included_type::giga::num - 1;
		}

		const int ec = threading::detail::condvar_timedwait(&cv, lk.mutex()->native_handle(), &ts);
		if (ec != 0 && ec != ETIMEDOUT) 
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
			THROW_SYSTEM_ERR_CODE(std, ec, condition_variable timed_wait failed)
#    else
			THROW_SYSTEM_ERR_CODE(boost::system, ec, condition_variable timed_wait failed)
#    endif
			;
	}
};

SROOK_INLINE_NAMESPACE_END
} // namespace cv

using cv::condition_variable;
using cv::cv_status;

} // namespace srook

#        undef CONDVAR_INLINE_INIT
#        undef THROW_SYSTEM_ERR_CODE
#        undef THROW_SYSTEM_ERR
#    else
#        error This environment is not supported.
#    endif
#endif
