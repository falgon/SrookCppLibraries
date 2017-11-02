// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONDITION_VARIABLE_DETAIL_CV_DETAIL_HPP
#define INCLUDED_SROOK_CONDITION_VARIABLE_DETAIL_CV_DETAIL_HPP

#include <cstdlib>
#include <srook/condition_variable/cv.hpp>
#include <srook/config/feature.hpp>
#include <srook/config/nullptr.hpp>

namespace srook {
namespace cv {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

struct at_thread_exit_elt {
    at_thread_exit_elt* next;
    void (*cb)(void*);
};

namespace {

threading::detail::tls_key_type key;

void at_thread_exit(at_thread_exit_elt*);

void run(void* ptr)
{
    at_thread_exit_elt* elt = static_cast<at_thread_exit_elt*>(ptr);
    while (elt) {
        at_thread_exit_elt* next = elt->next;
        elt->cb(elt);
        elt = next;
    }
}

void run()
{
    at_thread_exit_elt* elt = static_cast<at_thread_exit_elt*>(threading::detail::tls_get(key));
    threading::detail::tls_set(key, SROOK_NULLPTR);
    run(elt);
}

struct notifier : at_thread_exit_elt {
    notifier(condition_variable& c, unique_lock<mutex>& l) : cv(&c), mx(l.release())
    {
        cb = &notifier::run;
        at_thread_exit(this);
    }
    ~notifier()
    {
        mx->unlock();
        cv->notify_all();
    }

    condition_variable* cv;
    mutex* mx;

    static inline void run(void* ptr) SROOK_NOEXCEPT_TRUE
    {
        delete static_cast<notifier*>(ptr);
    }
};

void key_init()
{
    struct key_s {
        key_s() { threading::detail::tls_create(&key, run); }
        ~key_s() { threading::detail::tls_delete(key); }
    };
    static key_s ks;
    std::atexit(run);
}

void at_thread_exit(at_thread_exit_elt* elt)
{
    static threading::detail::exec_once_flag_type once = SROOK_EXEC_ONCE_INITIALIZER;
    threading::detail::execute_once(&once, key_init);

    elt->next = static_cast<at_thread_exit_elt*>(threading::detail::tls_get(key));
    threading::detail::tls_set(key, elt);
}

} // namespace
} // namespace detail

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT && !defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE)
void notify_all_at_thread_exit(condition_variable& cv, utility::cxx03::move_tag<unique_lock<mutex> > l)
{
    (void)new detail::notifier(cv, l.get());
}
#elif SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT && defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE)
SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
void notify_all_at_thread_exit(condition_variable& cv, unique_lock<mutex>& l)
{
    (void)new detail::notifier(cv, l);
}
#else
void notify_all_at_thread_exit(condition_variable& cv, unique_lock<mutex> l)
{
    (void)new detail::notifier(cv, l);
}
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace cv

using cv::notify_all_at_thread_exit;

} // namespace srook

#endif
