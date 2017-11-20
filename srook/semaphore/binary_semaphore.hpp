// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_SEMAPHOER_BINARY_SEMAPHORE_HPP
#define INCLUDED_SROOK_SEMAPHOER_BINARY_SEMAPHORE_HPP

#include <srook/condition_variable.hpp>
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature.hpp>
#include <srook/mutex.hpp>
#include <srook/utility.hpp>

namespace srook {
namespace semaphores {
SROOK_INLINE_NAMESPACE(v1)

template <class ConditionVariable, class Mutex>
class basic_binary_semapre : private noncopyable<basic_binary_semapre<ConditionVariable, Mutex> > {
    SROOK_STATIC_ASSERT(is_lockable<Mutex>::value, "Mutex must be lockable");

public:
    typedef Mutex mutex_type;
    typedef ConditionVariable condition_variable_type;
    typedef SROOK_DEDUCED_TYPENAME condition_variable_type::native_handle_type* native_handle_type;
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_CONSTEXPR basic_binary_semapre() SROOK_DEFAULT
    SROOK_CONSTEXPR explicit basic_binary_semapre(bool s) : signaled_(srook::move(s)) {}
#else
    SROOK_CONSTEXPR basic_binary_semapre() : counter_(false) {}
    SROOK_CONSTEXPR explicit basic_binary_semapre(bool s) : signaled_(s) {}
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
        signaled_ = false;
    }

    void down_interruptible()
    {
        down();
    }

    bool try_down()
    {
        lock_guard<mutex_type> lk(m_);
        if (!Instructor(*this)()) {
            signaled_ = false;
            return true;
        }
        return false;
    }

    void up()
    {
        const bool previously_signaled = signaled_;
        {
            lock_guard<mutex_type> lk(m_);
            signaled_ = true;
        }
        if (!previously_signaled) cv_.notify_one();
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
        SROOK_CONSTEXPR explicit Instructor(const basic_binary_semapre& bs) : b_(bs) {}
        SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator()() const { return !b_.signaled_; }

    private:
        const basic_binary_semapre& b_;
    };
    mutex_type m_;
    condition_variable_type cv_;
    bool signaled_
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = false
#endif
        ;
};

struct binary_semaphore
    : public basic_binary_semapre<srook::condition_variable, srook::mutex> {};

SROOK_INLINE_NAMESPACE_END
} // namespace semaphores

using semaphores::basic_binary_semapre;
using semaphores::binary_semaphore;

} // namespace srook

#endif
