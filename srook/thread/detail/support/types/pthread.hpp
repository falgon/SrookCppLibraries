// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_DETAIL_SUPPORT_TYPES_PTHREAD_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_SUPPORT_TYPES_PTHREAD_HPP

#include <srook/config/environment/os/thread_api.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/cpp_predefined.hpp>

#if SROOK_HAS_THREADS
#	if SROOK_HAS_THREAD_API_PTHREAD

#ifdef PTW32_VERSION
#	define HAVE_STRUCT_TIMESPEC 1
// for declare guard of timespec
// See also:
// http://mingw-users.1079350.n2.nabble.com/mingw-error-redefinition-of-struct-timespec-td7583722.html
#endif

#	include <pthread.h>
#	include <sched.h>
#   include <ctime>

namespace srook {
namespace thread {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

typedef pthread_mutex_t mutex_type;
typedef pthread_mutex_t recursive_mutex_type;
typedef pthread_cond_t cond_var_type;
typedef pthread_once_t exec_once_flag_type;
typedef pthread_t thread_id_type;
typedef pthread_t thread_type;
typedef pthread_key_t tls_key_type;

typedef 
// Not implemented yet in GCC 7.2.0...
// #if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
// std::timespec 
// #else
struct timespec 
// #endif
thread_time_type;

#   define SROOK_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
#ifdef PTHREAD_RECURSIVE_MUTEX_INITIALIZER
#   define SROOK_RECURSIVE_MUTEX_INITIALIZER PTHREAD_RECURSIVE_MUTEX_INITIALIZER
#elif defined(PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP)
#	define SROOK_RECURSIVE_MUTEX_INITIALIZER PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP
#endif
#   define SROOK_ERRORCHECK_MUTEX_INITIALIZER PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP 
#   define SROOK_COND_VAR_INITIALIZER PTHREAD_COND_INITIALIZER
#   define SROOK_EXEC_ONCE_INITIALIZER PTHREAD_ONCE_INIT
#   define SROOK_TLS_DESTRUCTOR_CC
#   define SROOK_NULL_THREAD SROOK_NULLPTR

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace thread
} // namespace srook

#   undef HAVE_STRUCT_TIMESPEC
#	endif
#    else
#        error not supported in this environment
#    endif
#endif
