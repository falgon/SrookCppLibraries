// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MUTEX_GUARDS_SCOPED_LOCK_HPP
#define INCLUDED_SROOK_MUTEX_GUARDS_SCOPED_LOCK_HPP
#include <srook/config/attribute/maybe_unused.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/mutex/guards/detail/lock_tags.hpp>
#include <srook/utility/noncopyable.hpp>

#if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && SROOK_HAS_INCLUDE(<boost/thread.hpp>)
#    define SCOPED_LOCK_BLOCK_BOOST_TAG   \
        SROOK_ATTRIBUTE_INLINE_VISIBILITY \
        explicit scoped_lock(boost::adopt_lock_t, mutex_type& m) SROOK_NOEXCEPT_TRUE : m_devices(m) {}
#else
#    define SCOPED_LOCK_BLOCK_BOOST_TAG   \
        SROOK_ATTRIBUTE_INLINE_VISIBILITY \
        explicit scoped_lock(std::adopt_lock_t, mutex_type& m) SROOK_NOEXCEPT_TRUE : m_devices(m) {}
#endif

#define DEF_SCOPED_LOCK_BLOCK                                                                   \
private                                                                                         \
    noncopyable<scoped_lock<Mutex> >                                                            \
    {                                                                                           \
    public:                                                                                     \
        typedef Mutex mutex_type;                                                               \
        explicit scoped_lock(mutex_type& m) : m_devices(m)                                      \
        {                                                                                       \
            m_devices.lock();                                                                   \
        }                                                                                       \
        explicit scoped_lock(adopt_lock_t, mutex_type& m) SROOK_NOEXCEPT_TRUE : m_devices(m) {} \
        SCOPED_LOCK_BLOCK_BOOST_TAG                                                             \
        ~scoped_lock()                                                                          \
        {                                                                                       \
            m_devices.unlock();                                                                 \
        }                                                                                       \
                                                                                                \
    private:                                                                                    \
        mutex_type& m_devices;                                                                  \
    }

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <mutex>
#    include <srook/mpl/variadic_types/pack.hpp>
#    include <srook/mutex/generic/lock.hpp>
#    include <srook/tuple/algorithm/apply.hpp>
#    include <srook/type_traits/conjunction.hpp>
#    include <srook/type_traits/library_concepts/is_mutex.hpp>
#    include <tuple>

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

template <class... Mutexes>
class scoped_lock : private noncopyable<scoped_lock<Mutexes...> > {
public:
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_STATIC_ASSERT(conjunction<is_mutex<Mutexes>...>::value, "The Mutexes must be mutex");
#    endif

    typedef srook::pack<Mutexes...> mutexes_type;

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    explicit scoped_lock(Mutexes&... m) : m_devices(std::tie(m...))
    {
        lock(m...);
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    explicit scoped_lock(adopt_lock_t, Mutexes&... m) SROOK_NOEXCEPT_TRUE : m_devices(std::tie(m...)) {}

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    explicit scoped_lock(std::adopt_lock_t, Mutexes&... m) SROOK_NOEXCEPT_TRUE : m_devices(std::tie(m...)) {}

    // boost::unique_lock is not supported
    // because when valid this block, the environment should able to use std::unique_lock.

    struct Unlocker {
        void operator()(Mutexes&... m) SROOK_NOEXCEPT_TRUE
        {
            SROOK_ATTRIBUTE_UNUSED char c[] = {(m.unlock(), 0)...};
        }
    };

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    ~scoped_lock()
    {
        srook::apply(Unlocker(), m_devices);
    }

private:
    const std::tuple<Mutexes&...> m_devices;
};

template <>
class scoped_lock<> : private noncopyable<scoped_lock<> > {
public:
    explicit scoped_lock() SROOK_DEFAULT
        explicit scoped_lock(adopt_lock_t) SROOK_NOEXCEPT_TRUE {}
    ~scoped_lock() SROOK_DEFAULT
};

template <class Mutex>
class scoped_lock<Mutex> : DEF_SCOPED_LOCK_BLOCK;

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT && SROOK_CPP_DEDUCTION_GUIDES
template <class... M>
scoped_lock(scoped_lock<M...>)->scoped_lock<M...>;
#    endif

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes

using mutexes::scoped_lock;

} // namespace srook

#    else
namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

template <class Mutex>
class scoped_lock : DEF_SCOPED_LOCK_BLOCK;

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes

using mutexes::scoped_lock;

} // namespace srook

#    endif
#    undef SCOPED_LOCK_BLOCK_BOOST_TAG
#    undef DEF_SCOPED_LOCK_BLOCK
#endif
