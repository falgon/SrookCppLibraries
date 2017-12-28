// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MEMORY_SINGLETON_MAYERS_SINGLETON_HPP
#define INCLUDED_SROOK_MEMORY_SINGLETON_MAYERS_SINGLETON_HPP

#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <srook/utility.hpp>

namespace srook {
namespace memory {

template <class T>
class mayers_singleton : private enable_copy_move<true, false, false, false> {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    template <class... Ts>
    SROOK_ATTRIBUTE_NODISCARD SROOK_FORCE_INLINE static reference
    instance(Ts&&... ts) SROOK_NOEXCEPT(is_nothrow_constructible<value_type>::value)
    {
        static value_type v{srook::forward<Ts>(ts)...};
        return v;
    }

    template <class... Ts>
    SROOK_ATTRIBUTE_NODISCARD SROOK_FORCE_INLINE static reference
    thread_local_instance(Ts&&... ts) SROOK_NOEXCEPT(is_nothrow_constructible<value_type>::value)
    {
        thread_local static value_type v{srook::forward<Ts>(ts)...};
        return v;
    }
protected:
    mayers_singleton() SROOK_DEFAULT
};

} // namespace memory

using memory::mayers_singleton;

} // namespace srook

#endif
