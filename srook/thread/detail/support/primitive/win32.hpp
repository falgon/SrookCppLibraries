#ifndef INCLUDED_SROOK_THREADS_DETAIL_PRIMITIVE_WIN32_HPP
#    define INCLUDED_SROOK_THREADS_DETAIL_PRIMITIVE_WIN32_HPP
#    include <srook/config/compiler/pragma/core.hpp>
#    include <srook/config/cpp_predefined/feature_testing.hpp>
#    include <srook/config/env.hpp>

#    if SROOK_HAS_THREADS && SROOK_HAS_THREAD_API_WIN32 && (SROOK_HAS_INCLUDE(<chrono>) || SROOK_HAS_INCLUDE(<boost/chrono.hpp>))
#        include <srook/config/attribute/force_inline.hpp>
#        include <srook/config/attribute/visibility.hpp>
#        include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#        include <srook/config/cpp_predefined/macro_names.hpp>
#        include <srook/config/feature/constexpr.hpp>
#        include <srook/config/feature/decltype.hpp>
#        include <srook/config/feature/explicit.hpp>
#        include <srook/config/feature/inline_namespace.hpp>
#        include <srook/config/libraries/nullptr.hpp>
#        include <srook/config/noexcept_detection.hpp>
#        include <srook/limits/numeric_limits.hpp>
#        include <srook/memory/utility/aggregate_adaptor.hpp>
#        include <srook/memory/utility/checked_delete.hpp>
#        include <srook/thread/detail/support/primitive/pthread.hpp>
#        include <srook/thread/detail/support/types.hpp>
#        include <srook/utility/declval.hpp>
#        include <srook/utility/move.hpp>
#        if SROOK_HAS_INCLUDE(<chrono>)
#            include <chrono>
#        elif SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#            include <boost/chrono.hpp>
#        endif

SROOK_PUSH_MACROS

#        ifdef min
#            undef min
#        endif
#        ifdef max
#            undef max
#        endif

namespace srook {
namespace threading {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

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

#            if SROOK_HAS_THREAD_API_WIN32
static inline int get_nprocs() SROOK_NOEXCEPT_TRUE
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
}
int recursive_mutex_init(recursive_mutex_type* m) { return InitializeCriticalSection(m), 0; }
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
bool thread_id_equal(thread_id_type lhs, thread_id_type rhs) SROOK_NOEXCEPT_TRUE { return lhs == rhs; }
bool thread_id_less(thread_id_type lhs, thread_id_type rhs) SROOK_NOEXCEPT_TRUE { return lhs < rhs; }

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
        Begin_threadex_thunk_data{f, arg}
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

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace thread
} // namespace srook

SROOK_POP_MACROS

#    endif
#else
#    error "This environment is not supported multi threading"
#endif
