// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MUTEX_RECURSIVE_MUTEX_HPP
#define INCLUDED_SROOK_MUTEX_RECURSIVE_MUTEX_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/exception.hpp>
#include <srook/mutex/mutexes/detail/recursive_mutex_base.hpp>
#include <srook/type_traits/library_concepts/is_mutex.hpp>
#include <srook/type_traits/is_nothrow_default_constructible.hpp>

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex"))
    recursive_mutex : private recursive_mutex_base {
public:
    typedef native_type* native_handle_type;

    recursive_mutex() SROOK_DEFAULT

    ~recursive_mutex() SROOK_DEFAULT

    recursive_mutex(const recursive_mutex&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE

    recursive_mutex& operator=(const recursive_mutex&) SROOK_EQ_DELETE

    void lock() SROOK_THREAD_SAFETY_ANNOTATION(acquire_capability())
    {
        const int e = thread::detail::recursive_mutex_lock(&m);
        if (e) {
            using namespace
#if SROOK_HAS_INCLUDE(<system_error>)
                std
#elif SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
                boost::system
#endif
                ;
            SROOK_THROW(system_error(error_code(e, system_category())));
        }
    }

    bool try_lock() SROOK_NOEXCEPT_TRUE SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        return thread::detail::recursive_mutex_trylock(&m);
    }

    void unlock() SROOK_NOEXCEPT_TRUE SROOK_THREAD_SAFETY_ANNOTATION(release_capability())
    {
        thread::detail::recursive_mutex_unlock(&m);
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY native_handle_type native_handle() SROOK_NOEXCEPT_TRUE
    {
        return &m;
    }
};

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_STATIC_ASSERT(is_mutex<recursive_mutex>::value, "");
#endif

SROOK_INLINE_NAMESPACE_END

} // namespace mutexes

using mutexes::recursive_mutex;

} // namespace srook

#endif
