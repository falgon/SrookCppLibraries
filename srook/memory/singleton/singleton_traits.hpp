// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_SINGLETON_SINGLETON_TRAITS_HPP
#define INCLUDED_SROOK_MEMORY_SINGLETON_SINGLETON_TRAITS_HPP

#include <srook/memory/singleton/singleton.hpp>
#include <srook/memory/singleton/mayers_singleton.hpp>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct singleton_traits;

template <class T, class A, class P>
struct singleton_traits<srook::memory::singleton<T, A, P>> : protected srook::memory::singleton<T, A, P> {
private:
    typedef srook::memory::singleton<T, A, P> specified_type;
public:
    typedef SROOK_DEDUCED_TYPENAME specified_type::friend_type friend_type;
    typedef SROOK_DEDUCED_TYPENAME specified_type::allocator_type allocator_type;
    typedef SROOK_DEDUCED_TYPENAME specified_type::traits_type traits_type;
    typedef SROOK_DEDUCED_TYPENAME specified_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME specified_type::pointer pointer;
    typedef SROOK_DEDUCED_TYPENAME specified_type::const_pointer const_pointer;
    typedef SROOK_DEDUCED_TYPENAME specified_type::reference reference;
    typedef SROOK_DEDUCED_TYPENAME specified_type::const_reference const_reference;

    using specified_type::instance;
    using specified_type::destroy;
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_ALIAS_TEMPLATES
    template <class TT, class AA = std::allocator<TT>, class PP = srook::memory::singleton_policy::use_default_ctors>
    using rebind_singleton = srook::memory::singleton<TT, AA, PP>;

    template <class TT, class AA = std::allocator<TT>, class PP = srook::memory::singleton_policy::use_default_ctors>
    using rebind_traits = singleton_traits<rebind_singleton<TT, AA, PP>>;
#endif

    SROOK_FORCE_INLINE static reference thread_local_instance() SROOK_EQ_DELETE
};

template <class T>
struct singleton_traits<srook::memory::mayers_singleton<T>> : protected srook::memory::mayers_singleton<T> {
private:
    typedef srook::memory::mayers_singleton<T> specified_type;
public:
    typedef SROOK_DEDUCED_TYPENAME specified_type::friend_type friend_type;
    typedef void allocator_type;
    typedef void traits_type;
    typedef SROOK_DEDUCED_TYPENAME specified_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME specified_type::pointer pointer;
    typedef SROOK_DEDUCED_TYPENAME specified_type::const_pointer const_pointer;
    typedef SROOK_DEDUCED_TYPENAME specified_type::reference reference;
    typedef SROOK_DEDUCED_TYPENAME specified_type::const_reference const_reference;

    using specified_type::instance;
    using specified_type::thread_local_instance;
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_ALIAS_TEMPLATES
    template <class TT>
    using rebind_singleton = srook::memory::mayers_singleton<T>;

    template <class TT>
    using rebind_traits = singleton_traits<rebind_singleton<TT>>;
#endif

    SROOK_FORCE_INLINE static void destroy() SROOK_EQ_DELETE
};

SROOK_INLINE_NAMESPACE_END
} // namespace memory

using memory::singleton_traits;

} // namespace srook

#endif
