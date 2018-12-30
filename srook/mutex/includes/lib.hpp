// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MUTEX_INCLUDES_LIB_HPP
#define INCLUDED_SROOK_MUTEX_INCLUDES_LIB_HPP

#include <srook/config/cpp_predefined.hpp>
#if (SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>) || SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)) && (SROOK_HAS_INCLUDE(<system_error>) || SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)) && (SROOK_HAS_INCLUDE(<ratio>) || SROOK_HAS_INCLUDE(<boost/ratio/ratio.hpp>))
#    include <srook/config/feature.hpp>
#    include <srook/config/attribute/noreturn.hpp>
#    include <srook/thread/detail/support.hpp>
#    if SROOK_HAS_INCLUDE(<chrono>) &&\
   	SROOK_HAS_INCLUDE(<system_error>) &&\
   	SROOK_HAS_INCLUDE(<mutex>) &&\
	SROOK_HAS_INCLUDE(<ratio>) &&\
   	SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#        include <chrono>
#        include <mutex>
#        include <system_error>
#        include <ratio>
#        define CHRONO_LIB std::chrono
#        define MUTEX_LIB std
#        define SROOK_HAS_STD_LOCK_TAG 1
#        define SROOK_HAS_BOOST_LOCK_TAG 0
#        define SYSERR_LIB std
#        define RATIO_LIB std
#    elif (SROOK_HAS_INCLUDE(<boost/chrono.hpp>) || SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)) && SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
#        if SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#            include <boost/chrono.hpp>
#        elif SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)
#            include <boost/chrono/include.hpp>
#        endif
#        include <boost/system/system_error.hpp>
#        include <boost/ratio/ratio.hpp>
#        define CHRONO_LIB boost::chrono
#        define SYSERR_LIB boost::system
#        define RATIO_LIB boost
#        define SROOK_HAS_STD_LOCK_TAG 0
#        if SROOK_HAS_INCLUDE(<boost/thread.hpp>)
#            include <boost/thread.hpp>
#            define MUTEX_LIB boost
#            define SROOK_HAS_BOOST_LOCK_TAG 1
#        endif
#        ifndef SROOK_HAS_BOOST_LOCK_TAG
#            define SROOK_HAS_BOOST_LOCK_TAG 0
#        endif
#    endif
#    if SROOK_HAS_THREADS && !defined(SROOK_THREAD_SAFETY_ANNOTATION) &&\
	 SROOK_HAS_THREAD_SAFETY_ANNOTATIONS
#        define SROOK_THREAD_SAFETY_ANNOTATION(x) __attribute__((x))
#    endif
#    ifndef SROOK_THREAD_SAFETY_ANNOTATION
#        define SROOK_THREAD_SAFETY_ANNOTATION(x)
#    endif
#    if SROOK_HAS_INCLUDE(<tuple>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#        include <tuple>
#        define TUPLE_LIB std
#    endif
#    include <srook/memory/unique_ptr.hpp>

namespace srook {
namespace mutexes {
namespace includes {
SROOK_INLINE_NAMESPACE(v1)

namespace chrono {
	using namespace CHRONO_LIB;
} // namespace chrono
#ifdef MUTEX_LIB
using MUTEX_LIB::mutex;
using MUTEX_LIB::recursive_mutex;
using MUTEX_LIB::timed_mutex;
using MUTEX_LIB::recursive_timed_mutex;
using MUTEX_LIB::adopt_lock_t;
using MUTEX_LIB::defer_lock_t;
using MUTEX_LIB::try_to_lock_t;
using MUTEX_LIB::adopt_lock;
using MUTEX_LIB::defer_lock;
using MUTEX_LIB::try_to_lock;
using MUTEX_LIB::unique_lock;
#endif
#ifdef TUPLE_LIB
using TUPLE_LIB::tuple;
using TUPLE_LIB::tuple_element;
using TUPLE_LIB::tuple_size;
using TUPLE_LIB::get;
using TUPLE_LIB::make_tuple;
#endif
using SYSERR_LIB::error_code;
using SYSERR_LIB::system_error;
using SYSERR_LIB::system_category;
#if SROOK_HAS_INCLUDE(<memory>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
using std::unique_ptr;
#elif SROOK_HAS_INCLUDE(<boost/unique_ptr.hpp>) && SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
using boost::unique_ptr;
#else
using srook::unique_ptr;
#endif

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
namespace errc {
	using namespace SYSERR_LIB::errc;
} // namespace errc
#define ERRC errc::errc_t
#else
using SYSERR_LIB::errc;
#define ERRC errc
#endif
using RATIO_LIB::ratio_greater;

SROOK_NORETURN void throw_system_err(int err, const char* mes = "")
{
	SROOK_THROW(system_error(error_code(err, system_category()), mes));
}

SROOK_NORETURN void throw_system_err(ERRC err, const char* mes = "")
{
	SROOK_THROW(system_error(error_code(static_cast<int>(err), system_category()), mes));
}
	
#undef CHRONO_LIB
#undef MUTEX_LIB
#undef SYSERR_LIB
SROOK_INLINE_NAMESPACE_END
} // namespace includes
} // namespace mutexes
} // namespace srook

#else
#    error This environment is not supported
#endif
#endif
