// C:opyright (C) 2017 roki
#ifndef INCLUDED_SROOK_SEMAPHOER_TIMED_SEMAPHORE_HPP
#define INCLUDED_SROOK_SEMAPHOER_TIMED_SEMAPHORE_HPP

#include <srook/semaphore/semaphore.hpp>

namespace srook {
namespace semaphores {
SROOK_INLINE_NAMESPACE(v1)

template <class ConditionVariable, class Mutex, class CounterType>
class basic_timed_semaphore : public basic_semaphore<ConditionVariable, Mutex, CounterType> {
    typedef basic_semaphore<ConditionVariable, Mutex, CounterType> base_type;

public:
    typedef SROOK_DEDUCED_TYPENAME base_type::counter_type counter_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::mutex_type mutex_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::condition_variable_type condition_variable_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::native_handle_type native_handle_type;
    SROOK_CONSTEXPR basic_timed_semaphore() SROOK_DEFAULT
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    using base_type::base_type;
#else
    SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE
    explicit basic_timed_semaphore(counter_type counter) : base_type(counter) {}
#endif
    template <class Rep, class Period>
    bool down_tryfor(const mutexes::includes::chrono::duration<Rep, Period>& d)
    {
        unique_lock<mutex_type> lk(this->m_);
        const bool b = !this->cv_.wait_for(lk, d, SROOK_DEDUCED_TYPENAME base_type::Instructor(*this));
        return !b ? --this->counter_, b : b;
    }

    template <class Clock, class Duration>
    bool down_tryuntil(const mutexes::includes::chrono::time_point<Clock, Duration>& t)
    {
        unique_lock<mutex_type> lk(this->m_);
        const bool b = !this->cv_.wait_until(lk, t, SROOK_DEDUCED_TYPENAME base_type::Instructor(*this));
        return !b ? --this->counter_, b : b;
    }

    template <class Rep, class Period>
    SROOK_FORCE_INLINE bool try_lock_for(const mutexes::includes::chrono::duration<Rep, Period>& d)
    {
        return !down_tryfor(d);
    }

    template <class Clock, class Duration>
    SROOK_FORCE_INLINE bool try_lock_until(const mutexes::includes::chrono::time_point<Clock, Duration>& t)
    {
        return !down_tryuntil(t);
    }
};

class timed_semaphore : public basic_timed_semaphore<srook::condition_variable, srook::mutex, std::size_t> {
    typedef basic_timed_semaphore<srook::condition_variable, srook::mutex, std::size_t> base_type;

public:
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    using base_type::base_type;
#else
    timed_semaphore(std::size_t max) : base_type(max) {}
#endif
};

SROOK_INLINE_NAMESPACE_END
} // namespace semaphores

using semaphores::basic_timed_semaphore;
using semaphores::timed_semaphore;

} // namespace srook

#endif
