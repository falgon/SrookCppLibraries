#ifndef INCLUDED_SROOK_THREADS_DETAIL_THREADING_SUPPORT_HPP
#define INCLUDED_SROOK_THREADS_DETAIL_THREADING_SUPPORT_HPP
#include <srook/config/compiler/pragma/core.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/env.hpp>

#    if SROOK_HAS_THREADS && (SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>))
#        include <srook/config/attribute/visibility.hpp>
#        include <srook/config/attribute/force_inline.hpp>
#        if SROOK_HAS_THREAD_API_PTHREAD
#            include <pthread.h>
#            include <sched.h>
#        elif SROOK_HAS_THREAD_API_WIN32
#            include <windows.h>
#            include <process.h>
#            include <fibersapi.h>
#        endif

SROOK_PUSH_MACROS

#        ifdef min
#            undef min
#        endif
#        ifdef max
#            undef max
#        endif

#        if SROOK_HAS_THREAD_API_EXTERNAL
#            define SROOK_THREAD_ABI_VISIBILITY SROOK_ATTRIBUTE_FUNCTION_VIS_DEFAULT
#        else
#            define SROOK_THREAD_ABI_VISIBILITY inline SROOK_ATTRIBUTE_INLINE_VISIBILITY
#        endif

#        ifdef _LIBCPP_NO_THREAD_SAFETY_ANALYSIS
#            define SROOK_NO_THREAD_SAFETY_ANALYSIS _LIBCPP_NO_THREAD_SAFETY_ANALYSIS
#        elif defined(__FreeBSD__) && defined(__clang__) && __has_attribute(no_thread_safety_analysis)
#            define SROOK_NO_THREAD_SAFETY_ANALYSIS __attribute__((no_thread_safety_analysis))
#        else
#            define SROOK_NO_THREAD_SAFETY_ANALYSIS
#        endif

#        if SROOK_HAS_INCLUDE(<chrono>)
#            include <chrono>
#        endif

#        if !SROOK_HAS_INCLUDE(<chrono>) && SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#            include <boost/chrono.hpp>
#        endif

#        include <srook/config/libraries/nullptr.hpp>
#        include <srook/config/feature/decltype.hpp>
#        include <srook/config/feature/constexpr.hpp>
#        include <srook/config/feature/inline_namespace.hpp>
#        include <srook/config/feature/explicit.hpp>
#        include <srook/limits/numeric_limits.hpp>
#        include <srook/utility/declval.hpp>
#        include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#        include <srook/config/cpp_predefined/macro_names.hpp>
#        include <srook/config/noexcept_detection.hpp>
#        if SROOK_HAS_THREAD_API_PTHREAD
#            include <errno.h>
#        endif
#        if SROOK_HAS_THREAD_API_WIN32 && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#            include <srook/memory/unique_ptr.hpp>
#            include <srook/memory/utility/aggregate_adaptor.hpp>
#            include <srook/utility/move.hpp>
#            include <srook/memory/utility/checked_delete.hpp>
#        endif

namespace srook {
namespace thread {
namespace mutex_collection {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

#        if SROOK_HAS_THREAD_API_PTHREAD
typedef pthread_mutex_t mutex_type;
#            define SROOK_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
typedef pthread_mutex_t recursive_mutex_type;
typedef pthread_cond_t cond_var_type;
#            define SROOK_COND_VAR_INITIALIZER PTHREAD_COND_INITIALIZER
typedef pthread_once_t exec_once_flag_type;
#            define SROOK_EXEC_ONCE_INITIALIZER PTHREAD_ONCE_INIT
typedef pthread_t thread_id_type;
#            define SROOK_NULL_THREAD SROOK_NULLPTR
typedef pthread_t thread_type;
typedef pthread_key_t tls_key_type;
#            define SROOK_TLS_DESTRUCTOR_CC
#        elif SROOK_HAS_THREAD_API_WIN32
typedef SRWLOCK mutex_type;
#            define SROOK_MUTEX_INITIALIZER SRWLOCK_INIT
typedef CRITICAL_SECTION recursive_mutex_type;
typedef CONDITION_VARIABLE cond_var_type;
#            define SROOK_COND_VAR_INITIALIZER CONDITION_VARIABLE_INIT
typedef INIT_ONCE exec_once_flag_type;
#            define SROOK_EXEC_ONCE_INITIALIZER INIT_ONCE_STATIC_INIT
typedef DWORD thread_id_type;
#            define SROOK_NULL_THREAD SROOK_NULLPTR
typedef HANDLE thread_type;
typedef DWORD tls_key_type;
#            define SROOK_TLS_DESTRUCTOR_CC WINAPI
#        endif

SROOK_THREAD_ABI_VISIBILITY int recursive_mutex_init(recursive_mutex_type*);
SROOK_THREAD_ABI_VISIBILITY SROOK_NO_THREAD_SAFETY_ANALYSIS int recursive_mutex_lock(recursive_mutex_type*);
SROOK_THREAD_ABI_VISIBILITY SROOK_NO_THREAD_SAFETY_ANALYSIS bool recursive_mutex_trylock(recursive_mutex_type*);
SROOK_THREAD_ABI_VISIBILITY SROOK_NO_THREAD_SAFETY_ANALYSIS int recursive_mutex_unlock(recursive_mutex_type*);
SROOK_THREAD_ABI_VISIBILITY int recursive_mutex_destroy(recursive_mutex_type*);
SROOK_THREAD_ABI_VISIBILITY SROOK_NO_THREAD_SAFETY_ANALYSIS int mutex_lock(mutex_type*);
SROOK_THREAD_ABI_VISIBILITY SROOK_NO_THREAD_SAFETY_ANALYSIS bool mutex_trylock(mutex_type*);
SROOK_THREAD_ABI_VISIBILITY SROOK_NO_THREAD_SAFETY_ANALYSIS int mutex_unlock(mutex_type*);
SROOK_THREAD_ABI_VISIBILITY int mutex_destroy(mutex_type*);
SROOK_THREAD_ABI_VISIBILITY int condvar_signal(cond_var_type*);
SROOK_THREAD_ABI_VISIBILITY int condvar_broadcast(cond_var_type*);
SROOK_THREAD_ABI_VISIBILITY SROOK_NO_THREAD_SAFETY_ANALYSIS int condvar_wait(cond_var_type*, mutex_type*);
SROOK_THREAD_ABI_VISIBILITY SROOK_NO_THREAD_SAFETY_ANALYSIS int condvar_timedwait(cond_var_type*, mutex_type*, timespec*);
SROOK_THREAD_ABI_VISIBILITY int condvar_destroy(cond_var_type*)
#        if SROOK_HAS_THREAD_API_WIN32
    SROOK_NOEXCEPT_TRUE
#        endif
    ;
SROOK_THREAD_ABI_VISIBILITY int execute_once(exec_once_flag_type*, void (*)());
SROOK_THREAD_ABI_VISIBILITY bool thread_id_equal(thread_id_type, thread_id_type) SROOK_NOEXCEPT_TRUE;
SROOK_THREAD_ABI_VISIBILITY bool thread_id_less(thread_id_type, thread_id_type) SROOK_NOEXCEPT_TRUE;
SROOK_THREAD_ABI_VISIBILITY bool thread_isnull(const thread_type*);
SROOK_THREAD_ABI_VISIBILITY int thread_create(thread_type*, void* (*)(void*), void*);
SROOK_THREAD_ABI_VISIBILITY thread_id_type thread_get_current_id();
SROOK_THREAD_ABI_VISIBILITY thread_id_type thread_get_id(const thread_type*);
SROOK_THREAD_ABI_VISIBILITY int thread_join(thread_type*);
SROOK_THREAD_ABI_VISIBILITY int thread_detach(thread_type*);
SROOK_THREAD_ABI_VISIBILITY void thread_yield();

#        if SROOK_HAS_INCLUDE(<chrono>)
SROOK_THREAD_ABI_VISIBILITY void thread_sleep_for(const std::chrono::nanoseconds&);
#        endif
#        if !SROOK_HAS_INCLUDE(<chrono>) && SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
SROOK_THREAD_ABI_VISIBILITY void thread_sleep_for(const boost::chrono::nanoseconds&);
#        endif

SROOK_THREAD_ABI_VISIBILITY int tls_create(tls_key_type*, void(SROOK_TLS_DESTRUCTOR_CC*)(void*));
SROOK_THREAD_ABI_VISIBILITY void* tls_get(tls_key_type);
SROOK_THREAD_ABI_VISIBILITY int tls_set(tls_key_type, void*);

// definition

#        if !SROOK_HAS_THREAD_API_EXTERNAL
#            ifdef SROOK_DECLTYPE
#                define SROOK_CPP03_DECLTYPE(x, y) SROOK_DECLTYPE(x)
#            else
#                define SROOK_CPP03_DECLTYPE(x, y) y
#            endif
#            if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#                define SROOK_CPP03_AUTO(x) auto
#            else
#                define SROOK_CPP03_AUTO(x) x
#            endif
#            if SROOK_HAS_THREAD_API_PTHREAD
int recursive_mutex_init(recursive_mutex_type* m)
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

int recursive_mutex_lock(recursive_mutex_type* m) { return pthread_mutex_lock(m); }
bool recursive_mutex_trylock(recursive_mutex_type* m) { return pthread_mutex_trylock(m) == 0; }
int recursive_mutex_unlock(mutex_type* m) { return pthread_mutex_unlock(m); }
int recursive_mutex_destroy(recursive_mutex_type* m) { return pthread_mutex_destroy(m); }
int mutex_lock(mutex_type* m) { return pthread_mutex_lock(m); }
bool mutex_trylock(mutex_type* m) { return pthread_mutex_trylock(m) == 0; }
int mutex_unlock(mutex_type* m) { return pthread_mutex_unlock(m); }
int mutex_destroy(mutex_type* m) { return pthread_mutex_destroy(m); }
int condvar_signal(cond_var_type* cv) { return pthread_cond_signal(cv); }
int condvar_broadcast(cond_var_type* cv) { return pthread_cond_broadcast(cv); }
int condvar_wait(cond_var_type* cv, mutex_type* m) { return pthread_cond_wait(cv, m); }
int condvar_timedwait(cond_var_type* cv, mutex_type* m, timespec* ts) { return pthread_cond_timedwait(cv, m, ts); }
int condvar_destroy(cond_var_type* cv) { return pthread_cond_destroy(cv); }
int execute_once(exec_once_flag_type* f, void (*init_routine)()) { return pthread_once(f, init_routine); }
bool thread_id_equal(thread_id_type t1, thread_id_type t2) SROOK_NOEXCEPT_TRUE { return pthread_equal(t1, t2) != 0; }
bool thread_id_less(thread_id_type t1, thread_id_type t2) SROOK_NOEXCEPT_TRUE { return t1 < t2; }
bool thread_isnull(const thread_type* t) { return *t == 0; }
int thread_create(thread_type* t, void* (*f)(void*), void* arg) { return pthread_create(t, 0, f, arg); }
thread_id_type thread_get_current_id() { return pthread_self(); }
thread_id_type thread_get_id(const thread_type* t) { return *t; }
int thread_join(thread_type* t) { return pthread_join(*t, 0); }
int thread_detach(thread_type* t) { return pthread_detach(*t); }
void thread_yield() { sched_yield(); }

#                if SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#                    define DEF_THREAD_SLEEP_FOR(LIB_NAMESPACE)                                                         \
                        void thread_sleep_for(const LIB_NAMESPACE::chrono::nanoseconds& ns)                             \
                        {                                                                                               \
                            using namespace LIB_NAMESPACE::chrono;                                                      \
                            seconds s = duration_cast<seconds>(ns);                                                     \
                            timespec ts;                                                                                \
                            typedef SROOK_CPP03_DECLTYPE(ts.tv_sec, time_t) ts_sec_type;                                \
                            SROOK_CONSTEXPR ts_sec_type sec_max = numeric_limits<ts_sec_type>::max();                   \
                            if (s.count() < sec_max) {                                                                  \
                                ts.tv_sec = static_cast<ts_sec_type>(s.count());                                        \
                                ts.tv_nsec = static_cast<SROOK_CPP03_DECLTYPE(ts.tv_nsec, long int)>((ns - s).count()); \
                            } else {                                                                                    \
                                ts.tv_sec = sec_max;                                                                    \
                                ts.tv_nsec = ((10 ^ 9) - 1);                                                            \
                            }                                                                                           \
                            while (nanosleep(&ts, &ts) == -1 && errno == EINTR);                                        \
                        }

#                    if SROOK_HAS_INCLUDE(<chrono>)
DEF_THREAD_SLEEP_FOR(std)
#                    endif
#                    if !SROOK_HAS_INCLUDE(<chrono>) && SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
DEF_THREAD_SLEEP_FOR(boost)
#                    endif
#                    undef DEF_THREAD_SLEEP_FOR
#                endif

int tls_create(tls_key_type* key, void (*at_exit)(void*))
{
    return pthread_key_create(key, at_exit);
}
void* tls_get(tls_key_type key) { return pthread_getspecific(key); }
int tls_set(tls_key_type key, void* p) { return pthread_setspecific(key, p); }

#            elif defined(SROOK_HAS_THREAD_API_WIN32)
int recursive_mutex_init(recursive_mutex_type* m)
{
    return InitializeCriticalSection(m), 0;
}
int recursive_mutex_lock(recursive_mutex_type* m) { return EnterCriticalSection(m), 0; }
bool recursive_mutex_trylock(recursive_mutex_type* m) { return TryEnterCriticalSection(m) != 0; }
int recursive_mutex_unlock(recursive_mutex_type* m) { return LeaveCriticalSection(m), 0; }
int recursive_mutex_destroy(recursive_mutex_type* m) { return DleteCriticalSection(m), 0; }
int mutex_lock(mutex_type* m) { return AcquireSRWLockExclusive(m), 0; }
bool mutex_trylock(mutex_type* m) { return TryAcquireSRWLockExclusive(m) != 0; }
int mutex_unlock(mutex_type* m) { return ReleaseSRWLockExclusive(m), 0; }
int mutex_destroy(mutex_type*) SROOK_NOEXCEPT_TRUE { return 0; }
int condvar_signal(cond_var_type* cv) { return WakeConditionVariable(cv), 0; }
int condvar_broadcast(cond_var_type* cv) { return WakeAllConditionVariable(cv), 0; }
int condvar_wait(cond_var_type* cv, mutex_type* m) { return SleepConditionVariableSRW(cv, m, INFINITE, 0), 0; }
int condvar_timedwait(cond_var_type* cv, mutex_type* m, timespec* ts)
{
    using namespace
#                if SROOK_HAS_INCLUDE(<chrono>)
        std::chrono
#                elif SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
        boost::chrono
#                endif
        ;

    SROOK_CPP03_AUTO(declval<nanoseconds>() + declval<seconds>(), nanoseconds)
    duration = seconds(ts->tv_sec) + nanoseconds(ts->tv_nsec);
    const SROOK_CPP03_AUTO(system_clock::time_point) abstime = system_clock::time_point(duration_cast<system_clock::duration>(duration));
    const SROOK_CPP03_AUTO(milliseconds) timeout_ms = duration_cast<milliseconds>(abstime - system_clock::now());

    if (!SleepConditionVariableSRW(cv, n, timeout_ms.count() > 0 ? timeout_ms.count() : 0, 0)) {
        const SROOK_CPP03_AUTO(DWORD) e = GetLastError();
        return e == ERROR_TIMEOUT ? ETIMEOUT : e;
    }
    return 0;
}
int condvar_destroy(cond_var_type*) SROOK_NOEXCEPT_TRUE { return 0; }
static inline SROOK_FORCE_INLINE BOOL CALLBACK
init_once_execute_once_thunk(PINIT_ONCE, PVOID param, PVOID*)
{
    void (*init_routine)() = reinterpret_cast<void (*)()>(param);
    init_routine();
    return TRUE;
}
int execute_once(exec_once_flag_type* f, void (*init_routine)())
{
    return !InitializeCriticalSection(f, init_once_execute_once_thunk, reinterpret_cast<void*>(init_routine), SROOK_NULLPTR)
               ? GetLastError()
               : 0;
}
bool thread_id_equal(thread_id_type lhs, thread_id_type rhs)
    SROOK_NOEXCEPT_TRUE { return lhs == rhs; }
bool thread_id_less(thread_id_type lhs, thread_id_type rhs)
    SROOK_NOEXCEPT_TRUE { return lhs < rhs; }

struct Begin_threadex_thunk_data {
#                if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
    SROOK_EXPLICIT Begin_threadex_thunk_data(void* (*fu)(void*), void* arg)
        : f(fu), arg(arg)
    {}
#                endif
    void* (*f)(void*);
    void* arg;
};

static inline SROOK_FORCE_INLINE unsigned WINAPI
begin_threadex_thunk(const Begin_threadex_thunk_data* const raw_data)
{
    void* (*f)(void*) = raw_data->f;
    void* arg = raw_data->arg;
    checked_delete(raw_data);
    return static_cast<unsigned>(reinterpret_cast<std::uintptr_t>(f(arg)));
}
bool thread_isnull(const thread_type* t) { return *t == 0; }
int thread_create(thread_type* t, void* (*f)(void*), void* arg)
{
    const Begin_threadex_thunk_data* const data = new
#                if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
        Begin_threadex_thunk_data(f, arg)
#                else
        Begin_threadex_thunk_data
    {
        f, arg
    }
#                endif
        ;
    *t = reinterpret_cast<HANDLE>(_beginthreadex(SROOK_NULLPTR, 0, begin_threadex_thunk, data, SROOK_NULLPTR));
    return *t ? 0 : GetLastError();
}
thread_id_type thread_get_current_id() { return GetCurrentThreadId(); }
thread_id_type thread_get_id(const thread_type* t) { return GetThreadId(*t); }
int thread_join(thread_type* t)
{
    return WaitForSingleObjectEx(*t, INFINITE, FALSE) == WAIT_FAILED ? GetLastError : !CloseHandle(*t) ? GetLastError() : 0;
}
int thread_detach(thread_type* t) { return !CloseHandle(*t) ? GetLastError() : 0; }
void thread_yield() { SwitchToThread(); }
#                if SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#                    define DEF_THREAD_SLEEP_FOR(LIB_NAMESPACE)                                            \
                        void thread_sleep_for(const LIB_NAMESPACE::chrono::nanoseconds& ns)                \
                        {                                                                                  \
                            using namespace LIB_NAMESPACE::chrono;                                         \
                            const milliseconds ms = duration_cast<milliseconds>(ns + nanoseconds(999999)); \
                            Sleep(ms.count());                                                             \
                        }
#                    if SROOK_HAS_INCLUDE(<chrono>)
DEF_THREAD_SLEEP_FOR(std)
#                    elif SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
DEF_THREAD_SLEEP_FOR(boost)
#                    endif
#                    undef DEF_THREAD_SLEEP_FOR
#                endif
void tls_create(
    tls_key_type* key,
    void(SROOK_TLS_DESTRUCTOR_CC* at_exit)(void*))
{
    return *key = FlsAlloc(at_exit), *key == FLS_OUT_OF_INDEXES ? GetLastError() : 0;
}
void* tls_get(tls_key_type* key) { return FlsGetValue(key); }
int tls_set(tls_key_type key, void* p) { return !FlsSetValue(key, p) ? GetLastError() : 0; }
#            endif
#            undef SROOK_CPP03_AUTO
#            undef SROOK_CPP03_DECLTYPE
#        endif
#    endif

} // detail
SROOK_INLINE_NAMESPACE_END
} // namespace mutex
} // namespace thread
} // namespace srook

SROOK_POP_MACROS

#else
#    error "This environment is not supported multi threading"
#endif
