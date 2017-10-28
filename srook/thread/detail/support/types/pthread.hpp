// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_DETAIL_SUPPORT_TYPES_PTHREAD_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_SUPPORT_TYPES_PTHREAD_HPP

#include <srook/config/environment/os/thread_api.hpp>
#include <srook/config/feature/inline_namespace.hpp>

#if SROOK_HAS_THREADS
#	if SROOK_HAS_THREAD_API_PTHREAD

#	include <pthread.h>
#	include <sched.h>

namespace srook {
namespace thread {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

typedef pthread_mutex_t mutex_type;
#        define SROOK_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
typedef pthread_mutex_t recursive_mutex_type;
typedef pthread_cond_t cond_var_type;
#        define SROOK_COND_VAR_INITIALIZER PTHREAD_COND_INITIALIZER
typedef pthread_once_t exec_once_flag_type;
#        define SROOK_EXEC_ONCE_INITIALIZER PTHREAD_ONCE_INIT
typedef pthread_t thread_id_type;
#        define SROOK_NULL_THREAD SROOK_NULLPTR
typedef pthread_t thread_type;
typedef pthread_key_t tls_key_type;
#        define SROOK_TLS_DESTRUCTOR_CC

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace thread
} // namespace srook

#	endif
#    else
#        error not supported in this environment
#    endif
#endif
