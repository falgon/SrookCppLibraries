// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_SEMAPHOER_SEMAPHORE_HPP
#define INCLUDED_SROOK_SEMAPHOER_SEMAPHORE_HPP

#include <cassert>
#include <srook/condition_variable.hpp>
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature.hpp>
#include <srook/mutex.hpp>
#include <srook/utility.hpp>

namespace srook {
namespace semaphores {
SROOK_INLINE_NAMESPACE(v1)

template <class ConditionVariable, class Mutex, class CounterType>
class basic_semaphore : private noncopyable<basic_semaphore<ConditionVariable, Mutex, CounterType> > {
    SROOK_STATIC_ASSERT((is_lockable<Mutex>::value), "Mutex must be Lockable");
    SROOK_STATIC_ASSERT((is_integral<CounterType>::value), "CounterType must be integral");

public:
    typedef Mutex mutex_type;
    typedef ConditionVariable condition_variable_type;
    typedef SROOK_DEDUCED_TYPENAME condition_variable_type::native_handle_type* native_handle_type;
    typedef CounterType counter_type;
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_CONSTEXPR basic_semaphore() SROOK_DEFAULT // The behavior is binary semaphore
    SROOK_CONSTEXPR explicit basic_semaphore(counter_type max) : counter_(max), max_(srook::move(max)) {}
#else
    SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE
    basic_semaphore() : counter_(1), max_(1) {} // The behavior is binary semaphore
    SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE
    explicit basic_semaphore(counter_type max) : counter_(max) max_(max) {}
#endif
    native_handle_type native_handle()
    SROOK_MEMFN_NOEXCEPT(declval<condition_variable_type>().native_handle())
    {
        return cv_.native_handle();
    }

    // The function name `down`, `down_xx` and `up` are inspired by linux kernel but `down` is interrputible.
    void down()
    {
        unique_lock<mutex_type> lk(m_);
        cv_.wait(lk, Instructor(*this));
        --counter_;
    }

    int down_interruptible()
    {
        down();
        return 0;
    }

    int down_trylock()
    {
        lock_guard<mutex_type> lk(m_);
        if (Instructor(*this)()) {
            --counter_;
            return 0;
        }
        return -1;
    }

    void up()
    {
        lock_guard<mutex_type> lk(m_);
        assert(counter_ < max_);
        ++counter_;
        cv_.notify_one();
    }

    void down_all()
    {
        lock_guard<mutex_type> lk(m_);
        counter_ = 0;
    }

    void up_all()
    {
        lock_guard<mutex_type> lk(m_);
        counter_ = max_;
        cv_.notify_all();
    }

    SROOK_CONSTEXPR counter_type max() const SROOK_NOEXCEPT_TRUE 
    { 
        lock_guard<mutex_type> lk(m_);
        return max_; 
    }
    SROOK_CONSTEXPR bool is_binary() const SROOK_NOEXCEPT_TRUE 
    { 
        lock_guard<mutex_type> lk(m_);
        return max_ == 1; 
    }
    SROOK_CONSTEXPR const counter_type& resource() const SROOK_NOEXCEPT_TRUE 
    {
        lock_guard<mutex_type> lk(m_);
        return counter_; 
    }

    // Lockable requirements [thread.req.lockable.req] for scoped guards.
    SROOK_FORCE_INLINE void lock() { down(); }
    SROOK_FORCE_INLINE bool try_lock() { return !down_trylock(); }
    SROOK_FORCE_INLINE void unlock() { up(); }

    // options...
    SROOK_FORCE_INLINE void lock_all() { down_all(); }
    SROOK_FORCE_INLINE void unlock_all() { up_all(); }

protected:
    struct Instructor {
        SROOK_CONSTEXPR explicit Instructor(const basic_semaphore& bs) : b_(bs) {}
        SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator()() const SROOK_NOEXCEPT_TRUE { return 0 < b_.counter_; }

    private:
        const basic_semaphore& b_;
    };
    mutable mutex_type m_;
    condition_variable_type cv_;
    counter_type counter_
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = 1
#endif
        ;
    const counter_type max_
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = 1
#endif
        ;
};

class semaphore : public basic_semaphore<srook::condition_variable, srook::mutex, std::size_t> {
    typedef basic_semaphore<srook::condition_variable, srook::mutex, std::size_t> base_type;

public:
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    using base_type::base_type;
#else
    SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE
    semaphore(std::size_t max) : base_type(max) {}
#endif
};

SROOK_INLINE_NAMESPACE_END
} // namespace semaphores

using semaphores::basic_semaphore;
using semaphores::semaphore;

} // namespace srook

#endif
