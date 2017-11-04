// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MUTEX_ONCE_HPP
#define INCLUDED_SROOK_MUTEX_ONCE_HPP

#include <srook/config/attribute/visibility.hpp>
#include <srook/functional/invoke.hpp>
#include <srook/memory/addressof.hpp>
#include <srook/mutex/guards/unique_lock.hpp>
#include <srook/mutex/mutexes/mutex.hpp>
#include <srook/thread/detail/support.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/utility/forward.hpp>
#include <srook/utility/noncopyable.hpp>

#ifndef SROOK_TLS
#    error this feature need TLS
#else

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

class SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT
    once_flag : private noncopyable<once_flag> {
    typedef threading::detail::exec_once_flag_type native_type;
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    native_type once = SROOK_EXEC_ONCE_INITIALIZER;
#    else
    static native_type once;
#    endif
public:
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    SROOK_CONSTEXPR once_flag() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
#    else
    SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    once_flag() SROOK_NOEXCEPT_TRUE {}
#    endif
        once_flag(const once_flag&) SROOK_EQ_DELETE
        once_flag&
        operator=(const once_flag&) SROOK_EQ_DELETE

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        template <class Callable, class... Args>
        SROOK_ATTRIBUTE_INLINE_VISIBILITY
        friend void call_once(once_flag&, Callable&&, Args&&...);
#    else
        SROOK_ATTRIBUTE_INLINE_VISIBILITY
        friend void call_once(once_flag&, void (*)());
#    endif
};
#    if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
once_flag::native_type once_flag::once = SROOK_EXEC_ONCE_INITIALIZER;
#    endif
namespace {

SROOK_TLS void* once_caller;
SROOK_TLS void (*once_call)();

} // namespace

extern "C" {
void once_proxy(void) { once_call(); }
}

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class Callable, class... Args>
SROOK_ATTRIBUTE_INLINE_VISIBILITY 
void call_once(once_flag& once, Callable&& f, Args&&... args)
{
    SROOK_STATIC_ASSERT((is_invocable<Callable, Args...>::value), "Callable must be callable");
    auto callable = [&] {
        invoke(srook::forward<Callable>(f), srook::forward<Args>(args)...);
    };
    once_caller = srook::addressof(callable);
    once_call = [] { (*(SROOK_DECLTYPE(callable)*)once_caller)(); };

    const int e = threading::detail::execute_once(&once.once, &once_proxy);

#        ifdef __clang_analyzer__
    once_caller = once_call = SROOK_NULLPTR;
#        endif
    if (e) includes::throw_system_err(e);
}
#    else

SROOK_ATTRIBUTE_INLINE_VISIBILITY
void call_once(once_flag& once, void (*f)())
{
    struct Caller {
        explicit Caller(void (*x)()) : f_(x) {}
        SROOK_ATTRIBUTE_INLINE_VISIBILITY
        void operator()() const
        {
            (f_)();
        }

    private:
        void (*f_)();
    } callable(f);

    once_caller = &callable;
    once_call = f;

    const int e = threading::detail::execute_once(&once.once, &once_proxy);
#        ifdef __clang_analyzer__
    once_caller once_call = SROOK_NULLPTR;
#        endif
    if (e) includes::throw_system_err(e);
}
#    endif

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes

using mutexes::call_once;
using mutexes::once_flag;

} // namespace srook

#endif
#endif
