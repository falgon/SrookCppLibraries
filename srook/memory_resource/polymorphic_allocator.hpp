// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_RESOURCE_POLYMORPHIC_ALLOCATOR_HPP
#define INCLUDED_SROOK_MEMORY_RESOURCE_POLYMORPHIC_ALLOCATOR_HPP

#include <srook/memory_resource/memory_resource.hpp>
#include <srook/memory_resource/global_memory_resources.hpp>
#include <srook/type_traits.hpp>
#include <srook/memory/addressof.hpp>
#include <srook/memory/launder.hpp>
#include <srook/mpl/variadic_types.hpp>
#include <srook/utility.hpp>
#include <cassert>

namespace srook {
namespace pmr {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

struct alloc_base {};

struct alloc_b0 : alloc_base {
    struct sink {
        void operator=(const void*) {}
    } a_;
};

template <class Allocator>
struct alloc_b1 : alloc_base {
    typedef Allocator allocator_type;
    const Allocator* a_;
};

template <class Allocator>
struct alloc_b2 : alloc_base {
    typedef Allocator allocator_type;
    const Allocator* a_;
};

template <bool, class, class, class...>
struct uses_alloca : alloc_b0 {};

template <class T, class Allocator, class... Args>
struct uses_alloca<true, T, Allocator, Args...> 
    : conditional<is_constructible<T, std::allocator_arg_t, Allocator, Args...>::value, alloc_b1<Allocator>, alloc_b2<Allocator>>::type
{
    SROOK_STATIC_ASSERT((
        type_traits::detail::Lor<
            is_constructible<T, std::allocator_arg_t, Allocator, Args...>, 
            is_constructible<T, std::allocator_arg_t, Allocator, Args...>, 
            is_constructible<T, Args..., Allocator>
        >::value),
        "construction with an allocator must be possible if uses_allocator is true");
};


template <class T, class Allocator, class... Args>
SROOK_FORCE_INLINE uses_alloca<std::uses_allocator<T, Allocator>::value, T, Allocator, Args...> use_alloc(const Allocator& a)
{
    uses_alloca<std::uses_allocator<T, Allocator>::value, T, Allocator, Args...> ret;
    ret.a_ = srook::addressof(a);
    return ret;
}

template <class, class Alloc, class...>
void use_alloc(const Alloc&&) SROOK_EQ_DELETE

} // namespace detail

template <class T>
class polymorphic_allocator {
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

#if SROOK_CPP_ALIAS_TEMPLATES
    template <class U>
    struct rebind {
        using other = polymorphic_allocator<U>;
    };
#endif


private:
    typedef SROOK_DEDUCED_TYPENAME add_pointer<SROOK_DEDUCED_TYPENAME detail::core_type<detail::has_base_type<memory_resource>::value>::type>::type core_resource_pointer_type;
    typedef detail::alloc_b1<core_resource_pointer_type> uses_alloc1;
    typedef detail::alloc_b2<core_resource_pointer_type> uses_alloc2;

    template <class U, class... Args>
    void do_construct(detail::alloc_b0, U* p, Args&&... args)
    {
        ::new(p) T(srook::forward<Args>(args)...);
    }

    template <class U, class... Args>
    void do_construct(uses_alloc1, U* p, Args&&... args)
    {
        ::new(p) T(std::allocator_arg, resource(), srook::forward<Args>(args)...);
    }

    template <class U, class... Args>
    void do_construct(uses_alloc2, T* p, Args&&... args)
    {
        ::new(p) T(srook::forward<Args>(args)..., resource());
    }

    template <class Tuple>
    SROOK_FORCE_INLINE Tuple&& do_construct_pair(detail::alloc_b0, Tuple& t) { return srook::move(t); }

    template <class... Args>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Transfer<
        std::tuple,
        SROOK_DEDUCED_TYPENAME Concat<
            pack<std::allocator_arg_t, SROOK_DEDUCED_TYPENAME add_pointer<SROOK_DEDUCED_TYPENAME uses_alloc1::allocator_type>::type>,
            pack<Args...>
        >::type
    >::type do_construct_pair(uses_alloc1 ua, std::tuple<Args...>& t)
    {
        return std::tuple_cat(std::make_tuple(std::allocator_arg, *(ua.a_)), srook::move(t));
    }

    template <class... Args>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Transfer<
        std::tuple,
        SROOK_DEDUCED_TYPENAME Concat<
            pack<Args...>,
            pack<SROOK_DEDUCED_TYPENAME add_pointer<SROOK_DEDUCED_TYPENAME uses_alloc2::allocator_type>::type>
        >::type
    >::type do_construct_pair(uses_alloc2 ua, std::tuple<Args...>& t)
    {
        return std::tuple_cat(srook::move(t), std::make_tuple(*(ua.a_)));
    }
public:
    typedef T value_type;

    polymorphic_allocator() SROOK_NOEXCEPT_TRUE
        : resource_(get_default_resource()) {}

    polymorphic_allocator(core_resource_pointer_type r)
        : resource_(r)
    {
        assert(r);
    }

    polymorphic_allocator& operator=(const polymorphic_allocator) SROOK_EQ_DELETE

    template <class U>
    polymorphic_allocator(const polymorphic_allocator<U>& other) SROOK_NOEXCEPT_TRUE
        : resource_(other.resource()) {}

    SROOK_FORCE_INLINE T* allocate(std::size_t n) { return static_cast<T*>(resource_->allocate(n * sizeof(T), SROOK_ALIGN_OF(T))); }
    SROOK_FORCE_INLINE void deallocate(T* p, std::size_t n) { resource_->deallocate(p, n * sizeof(T), SROOK_ALIGN_OF(T)); }
    
    template <class U, class... Args>
    void construct(U* p, Args&&... args)
    {
        const core_resource_pointer_type rs = resource();
        do_construct(detail::use_alloc<U, core_resource_pointer_type, Args...>(rs), p, srook::forward<Args>(args)...);
    }

    template <class U1, class U2, class... Args1, class... Args2>
    void construct(std::pair<U1, U2>* p, std::piecewise_construct_t, std::tuple<Args1...> x, std::tuple<Args2...> y)
    {
        const core_resource_pointer_type rs = resource();
        ::new(p) std::pair<U1, U2>(std::piecewise_construct, 
                do_construct_pair(detail::use_alloc<U1, core_resource_pointer_type, Args1...>(rs), x), 
                do_construct_pair(detail::use_alloc<U2, core_resource_pointer_type, Args2...>(rs)));
    }

    template <class U1, class U2>
    void construct(std::pair<U1, U2>* p)
    {
        construct(p, std::piecewise_construct, std::make_tuple(), std::make_tuple());
    }

    template <class U1, class U2, class U3, class U4>
    void construct(std::pair<U1, U2>* p, std::pair<U3, U4>& pr)
    {
        construct(p, std::piecewise_construct, std::forward_as_tuple(pr.first), std::forward_as_tuple(pr.second));
    }

    template <class U1, class U2, class U3, class U4>
    void construct(std::pair<U1, U2>* p, std::pair<U3, U4>&& pr)
    {
        construct(p, std::piecewise_construct, std::forward_as_tuple(srook::forward<U3>(pr.first), srook::forward<U4>(pr.second)));
    }

    template <class U>
    void destroy(U* p)
    {
        srook::launder(p)->~U();
    }

    polymorphic_allocator select_on_container_copy_construction() const { return polymorphic_allocator(); }

    core_resource_pointer_type resource() const { return resource_; }
private:
    core_resource_pointer_type resource_;
};

template <class T1, class T2>
SROOK_FORCE_INLINE bool operator==(const polymorphic_allocator<T1>& lhs, const polymorphic_allocator<T2>& rhs) SROOK_NOEXCEPT_TRUE
{
    return *lhs.resource() == *rhs.resource();
}

template <class T1, class T2>
SROOK_FORCE_INLINE bool operator!=(const polymorphic_allocator<T1>& lhs, const polymorphic_allocator<T2> rhs) SROOK_NOEXCEPT_TRUE
{
    return !(lhs == rhs);
}

SROOK_INLINE_NAMESPACE_END
} // namespace pmr
} // namespace srook

#endif
