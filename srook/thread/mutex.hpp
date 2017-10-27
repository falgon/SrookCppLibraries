// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_MUTEX_HPP
#define INCLUDED_SROOK_THREAD_MUTEX_HPP

#include <srook/thread/detail/mutex_base.hpp>
#include <srook/thread/detail/lock_tags.hpp>

namespace srook {
namespace thread {
namespace mutex_collection {
SROOK_INLINE_NAMESPACE(v1)

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex")) 
mutex : private mutex_base {
public:
    typedef native_type* native_handle_type;
    SROOK_CONSTEXPR mutex() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
    ~mutex() SROOK_DEFAULT
    mutex(const mutex&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE
    mutex& operator=(const mutex&) SROOK_EQ_DELETE

    void lock() SROOK_THREAD_SAFETY_ANNOTATION(acquire_capability())
    {
        const int e = detail::mutex_lock(&m);
        if (e) {
            using namespace
#if SROOK_HAS_INCLUDE(<system_error>)
                std
#elif SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
                boost::system
#endif
                ;
            error_code ec(e, std::system_category());
            throw system_error(ec, "operation not permitted");
        }
    }

    bool try_lock() SROOK_NOEXCEPT_TRUE SROOK_THREAD_SAFETY_ANNOTATION(try_acquire_capability(true))
    {
        return !detail::mutex_trylock(&m);
    }

    void unlock() SROOK_NOEXCEPT_TRUE SROOK_THREAD_SAFETY_ANNOTATION(release_capability())
    {
        detail::mutex_unlock(&m);
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY native_handle_type native_handle() SROOK_NOEXCEPT_TRUE
    {
        return &m;
    }
};

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_STATIC_ASSERT(
		is_nothrow_default_constructible<mutex>::value,
                    "the default constructor for srook::mutex must be nothrow");
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace mutex_collection

using mutex_collection::mutex;

} // namespace thread

using thread::mutex;
} // namespace srook

#endif
