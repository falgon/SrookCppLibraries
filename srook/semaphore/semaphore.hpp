// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_SEMAPHOER_SEMAPHORE_HPP
#define INCLUDED_SROOK_SEMAPHOER_SEMAPHORE_HPP

#include <srook/condition_variable.hpp>
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/mutex.hpp>
#include <srook/utility.hpp>

namespace srook {
namespace semaphores {
SROOK_INLINE_NAMESPACE(v1)

template <class ConditionVariable, class Mutex, class CounterType>
class basic_semaphore : private noncopyable<basic_semaphore<ConditionVariable, Mutex, CounterType> > {
    SROOK_STATIC_ASSERT((is_lockable<Mutex>::value), "Mutex must be lockable");
    SROOK_STATIC_ASSERT((is_arithmetic<CounterType>::value), "CounterType must be arithmetic");

public:
    typedef Mutex mutex_type;
    typedef ConditionVariable condition_variable_type;
    typedef SROOK_DEDUCED_TYPENAME condition_variable_type::native_handle_type* native_handle_type;
    typedef CounterType counter_type;
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_CONSTEXPR basic_semaphore() SROOK_DEFAULT
    SROOK_CONSTEXPR explicit basic_semaphore(counter_type counter) : counter_(srook::move(counter)) {}
#else
    SROOK_CONSTEXPR basic_semaphore() : counter_(0) {}
    SROOK_CONSTEXPR explicit basic_semaphore(counter_type counter) : counter_(counter) {}
#endif
    native_handle_type native_handle()
    SROOK_MEMFN_NOEXCEPT(declval<condition_variable_type>().native_handle())
    {
        return cv_.native_handle();
    }

    // The function name `down` and `up` are inspired by linux kernel but `down` is interrputible.
    void down()
    {
        unique_lock<mutex_type> lk(m_);
        cv_.wait(lk, Instructor(*this));
        --counter_;
    }

    void down_interruptible()
    {
        down();
    }

    bool try_down()
    {
        lock_guard<mutex_type> lk(m_);
        if (!Instructor(*this)()) {
            --counter_;
            return true;
        }
        return false;
    }

    void up()
    {
        lock_guard<mutex_type> lk(m_);
        assert(counter_ >= numeric_limits<counter_type>::max());
        ++counter_;
        cv_.notify_one();
    }

    // Lockable requirements [thread.req.lockable.req] for scoped gurads.
    SROOK_FORCE_INLINE void lock()
    {
        down();
    }

    SROOK_FORCE_INLINE bool try_lock()
    {
        return try_down();
    }

    SROOK_FORCE_INLINE void unlock()
    {
        up();
    }

protected:
    struct Instructor {
        SROOK_CONSTEXPR explicit Instructor(const basic_semaphore& bs) : b_(bs) {}
        SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator()() const { return !b_.counter_; }

    private:
        const basic_semaphore& b_;
    };
    mutex_type m_;
    condition_variable_type cv_;
    counter_type counter_
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = 0
#endif
        ;
};

struct semaphore
    : public basic_semaphore<srook::condition_variable, srook::mutex, std::size_t> {};

SROOK_INLINE_NAMESPACE_END
} // namespace semaphores

using semaphores::basic_semaphore;
using semaphores::semaphore;

} // namespace srook

#endif
