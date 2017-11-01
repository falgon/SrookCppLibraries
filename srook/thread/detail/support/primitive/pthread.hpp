#ifndef INCLUDED_SROOK_THREADS_DETAIL_SUPPORT_PRIMITIVE_PTHREAD_HPP
#define INCLUDED_SROOK_THREADS_DETAIL_SUPPORT_PRIMITIVE_PTHREAD_HPP

#include <srook/config/compiler/pragma/core.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/env.hpp>

#if SROOK_HAS_THREADS && SROOK_HAS_THREAD_API_PTHREAD &&\
   	(SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>)) &&\
   	!SROOK_HAS_THREAD_API_EXTERNAL
#    include <errno.h>
#    include <srook/config/attribute/force_inline.hpp>
#    include <srook/config/attribute/visibility.hpp>
#    include <srook/config/feature/constexpr.hpp>
#    include <srook/config/feature/decltype.hpp>
#    include <srook/config/feature/explicit.hpp>
#    include <srook/config/feature/inline_namespace.hpp>
#    include <srook/config/libraries/nullptr.hpp>
#    include <srook/config/noexcept_detection.hpp>
#    include <srook/limits/numeric_limits.hpp>
#    include <srook/thread/detail/support/types.hpp>
#    include <srook/utility/declval.hpp>
#    if SROOK_HAS_INCLUDE(<chrono>)
#        include <chrono>
#    elif SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#        include <boost/chrono.hpp>
#    endif

//SROOK_PUSH_MACROS

#    ifdef min
#        undef min
#    endif
#    ifdef max
#        undef max
#    endif

namespace srook {
namespace thread {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

#    if !SROOK_HAS_THREAD_API_EXTERNAL
#        ifdef SROOK_DECLTYPE
#            define SROOK_CPP03_DECLTYPE(x, y) SROOK_DECLTYPE(x)
#        else
#            define SROOK_CPP03_DECLTYPE(x, y) y
#        endif
#        if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#            define SROOK_CPP03_AUTO(x) auto
#        else
#            define SROOK_CPP03_AUTO(x) x
#        endif

static int recursive_mutex_init(recursive_mutex_type* m)
{
    pthread_mutexattr_t attr;
    int e = pthread_mutexattr_init(&attr);
    if (e) return e;

    e = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    if (e) {
        pthread_mutexattr_destroy(&attr);
        return e;
    }
    e = pthread_mutex_init(m, &attr);
    if (e) {
        pthread_mutexattr_destroy(&attr);
        return e;
    }
    e = pthread_mutexattr_destroy(&attr);
    if (e) {
        pthread_mutex_destroy(m);
        return e;
    }
    return 0;
}

static int recursive_mutex_lock(recursive_mutex_type* m) 
{ 
	return pthread_mutex_lock(m); 
}
static bool recursive_mutex_trylock(recursive_mutex_type* m) 
{ 
	return pthread_mutex_trylock(m) == 0; 
}
static int recursive_mutex_unlock(mutex_type* m) 
{ 
	return pthread_mutex_unlock(m); 
}
static int recursive_mutex_destroy(recursive_mutex_type* m) 
{ 
	return pthread_mutex_destroy(m); 
}
static int mutex_lock(mutex_type* m) 
{ 
	return pthread_mutex_lock(m); 
}
static bool mutex_trylock(mutex_type* m) 
{ 
	return pthread_mutex_trylock(m) == 0; 
}
static int mutex_unlock(mutex_type* m) 
{ 
	return pthread_mutex_unlock(m); 
}
static int mutex_destroy(mutex_type* m) 
{ 
	return pthread_mutex_destroy(m); 
}
#if SROOK_PTHREAD_TIMEOUTS_SUPPORT
static int mutex_timedlock(mutex_type* m, const thread_time_type* ts) 
{ 
	return pthread_mutex_timedlock(m, ts) == 0;
}
#endif
static int condvar_signal(cond_var_type* cv) 
{ 
	return pthread_cond_signal(cv); 
}
static int condvar_broadcast(cond_var_type* cv) 
{ 
	return pthread_cond_broadcast(cv); 
}
static int condvar_wait(cond_var_type* cv, mutex_type* m) 
{ 
	return pthread_cond_wait(cv, m); 
}
static int condvar_timedwait(cond_var_type* cv, mutex_type* m, thread_time_type* ts) 
{ 
	return pthread_cond_timedwait(cv, m, ts); 
}
static int condvar_destroy(cond_var_type* cv) 
{ 
	return pthread_cond_destroy(cv); 
}
static int execute_once(exec_once_flag_type* f, void (*init_routine)()) 
{ 
	return pthread_once(f, init_routine); 
}
static bool thread_id_equal(thread_id_type t1, thread_id_type t2) SROOK_NOEXCEPT_TRUE 
{ 
	return pthread_equal(t1, t2) != 0; 
}
static bool thread_id_less(thread_id_type t1, thread_id_type t2) SROOK_NOEXCEPT_TRUE 
{ 
	return t1 < t2; 
}
static bool thread_isnull(const thread_type* t) 
{ 
	return *t == 0; 
}
static int thread_create(thread_type* t, void* (*f)(void*), void* arg) 
{ 
	return pthread_create(t, 0, f, arg); 
}
static thread_id_type thread_get_current_id() 
{ 
	return pthread_self(); 
}
static thread_id_type thread_get_id(const thread_type* t) 
{ 
	return *t; 
}
static int thread_join(thread_type* t) 
{ 
	return pthread_join(*t, 0); 
}
static int thread_detach(thread_type* t) 
{ 
	return pthread_detach(*t); 
}
static void thread_yield() 
{ 
	sched_yield(); 
}
#        if SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#            define DEF_THREAD_SLEEP_FOR(LIB_NAMESPACE)                                                         \
                static void thread_sleep_for(const LIB_NAMESPACE::chrono::nanoseconds& ns)                      \
                {                                                                                               \
                    using namespace LIB_NAMESPACE::chrono;                                                      \
                    seconds s = duration_cast<seconds>(ns);                                                     \
                    thread_time_type ts;                                                                        \
                    typedef SROOK_CPP03_DECLTYPE(ts.tv_sec, time_t) ts_sec_type;                                \
                    SROOK_CONSTEXPR ts_sec_type sec_max = numeric_limits<ts_sec_type>::max();                   \
                    if (s.count() < sec_max) {                                                                  \
                        ts.tv_sec = static_cast<ts_sec_type>(s.count());                                        \
                        ts.tv_nsec = static_cast<SROOK_CPP03_DECLTYPE(ts.tv_nsec, long int)>((ns - s).count()); \
                    } else {                                                                                    \
                        ts.tv_sec = sec_max;                                                                    \
                        ts.tv_nsec = ((10 ^ 9) - 1);                                                            \
                    }                                                                                           \
                    while (nanosleep(&ts, &ts) == -1 && errno == EINTR)                                         \
                        ;                                                                                       \
                }

#            if SROOK_HAS_INCLUDE(<chrono>)
DEF_THREAD_SLEEP_FOR(std)
#            endif
#            if !SROOK_HAS_INCLUDE(<chrono>) && SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
DEF_THREAD_SLEEP_FOR(boost)
#            endif
#            undef DEF_THREAD_SLEEP_FOR
#        endif

static int tls_create(tls_key_type* key, void (*at_exit)(void*))
{
    return pthread_key_create(key, at_exit);
}
static void* tls_get(tls_key_type key) 
{ 
	return pthread_getspecific(key); 
}
static int tls_set(tls_key_type key, void* p) 
{ 
	return pthread_setspecific(key, p); 
}
static int tls_delete(tls_key_type key) 
{ 
	return pthread_key_delete(key); 
}

} // detail
SROOK_INLINE_NAMESPACE_END
} // namespace thread
} // namespace srook

//SROOK_POP_MACROS
#        endif
#    else
#        error "This environment is not supported multi threading"
#    endif
#endif
