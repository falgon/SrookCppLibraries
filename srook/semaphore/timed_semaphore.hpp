// C:opyright (C) 2017 roki
#ifndef INCLUDED_SROOK_SEMAPHOER_TIMED_SEMAPHORE_HPP
#define INCLUDED_SROOK_SEMAPHOER_TIMED_SEMAPHORE_HPP

#include <srook/semaphore/semaphore.hpp>

namespace srook {
namespace semaphores {
SROOK_INLINE_NAMESPACE(v1)

template <class ConditionVariable, class Mutex, class CounterType>
class timed_basic_semaphore : public basic_semaphore<ConditionVariable, Mutex, CounterType> {
    typedef basic_semaphore<ConditionVariable, Mutex, CounterType> base_type;
    SROOK_STATIC_ASSERT((type_traits::detail::Land<is_lockable<Mutex> >::value), "Mutex must be lockable");
    SROOK_STATIC_ASSERT((is_arithmetic<CounterType>::value), "CounterType must be arithmetic");

public:
    typedef SROOK_DEDUCED_TYPENAME base_type::counter_type counter_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::mutex_type mutex_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::condition_variable_type condition_variable_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::native_handle_type native_handle_type;
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_CONSTEXPR timed_basic_semaphore() SROOK_DEFAULT
    SROOK_CONSTEXPR explicit timed_basic_semaphore(counter_type counter) : base_type(srook::move(counter)) {}
#else
    SROOK_CONSTEXPR timed_basic_semaphore() : counter_(0) {}
    SROOK_CONSTEXPR explicit timed_basic_semaphore(counter_type counter) : base_type(counter) {}
#endif
    native_handle_type native_handle()
    SROOK_MEMFN_NOEXCEPT(declval<condition_variable_type>().native_handle())
    {
        return base_type::native_handle();
    }

    template <class Rep, class Period>
    bool try_down_for(const mutexes::includes::chrono::duration<Rep, Period>& d)
    {
        unique_lock<mutex_type> lk(this->m_);
        const bool b = this->cv_.wait_for(lk, d, SROOK_DEDUCED_TYPENAME base_type::Instructor(*this));
        return b ? --this->counter_, b : b;
    }

    template <class Clock, class Duration>
    bool try_down_until(const mutexes::includes::chrono::time_point<Clock, Duration>& t)
    {
        unique_lock<mutex_type> lk(this->m_);
        const bool b = this->cv_.wait_until(lk, t, SROOK_DEDUCED_TYPENAME base_type::Instructor(*this));
        return b ? --this->counter_, b : b;
    }

    template <class Rep, class Period>
    SROOK_FORCE_INLINE bool try_lock_for(const mutexes::includes::chrono::duration<Rep, Period>& d)
    {
        return try_down_for(d);
    }

    template <class Clock, class Duration>
    SROOK_FORCE_INLINE bool try_lock_until(const mutexes::includes::chrono::time_point<Clock, Duration>& t)
    {
        return try_down_until(t);
    }
};

struct timed_semaphore
    : public timed_basic_semaphore<srook::condition_variable, srook::mutex, std::size_t> {};

SROOK_INLINE_NAMESPACE_END
} // namespace semaphores

using semaphores::timed_basic_semaphore;
using semaphores::timed_semaphore;

} // namespace srook

#endif
