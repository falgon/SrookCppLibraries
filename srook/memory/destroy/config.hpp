// Copyright (C) 2011-2019 Roki. Distributed under the MIT License.
#ifndef INCLUDED_SROOK_MEMORY_DESTORY_CONFIG_HPP
#define INCLUDED_SROOK_MEMORY_DESTORY_CONFIG_HPP

#include <srook/config.hpp>

#ifdef SROOK_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <srook/iterator/range_access/advance.hpp>
#include <srook/iterator/range_access/next.hpp>
#include <srook/type_traits/is_nothrow_destructible.hpp>
#include <srook/type_traits/has_trivial_destructor.hpp>
#include <srook/type_traits/is_incrementable.hpp>
#include <srook/type_traits/is_decrementable.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/type_traits/is_gt_comparable.hpp>
#include <srook/algorithm/detail/config.hpp>
#include <srook/memory/addressof.hpp>

#if SROOK_HAS_CONCEPTS
#   include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#   define SROOK_FORWARDITER_REQUIRE_TEMPLATE(X)\
    template <class X> requires srook::concepts::ForwardIterator<X> || is_pointer<X>::value
#   define SROOK_FORWARDITER_REQUIRE_TEMPLATE_WITH_SIZE(X, S)\
    template <class X, typename S> requires srook::concepts::ForwardIterator<X> || is_pointer<X>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#   include <srook/type_traits/iterator/is_forwarditerator.hpp>
#   define SROOK_FORWARDITER_REQUIRE_TEMPLATE(X)\
    template <class X, SROOK_REQUIRES(is_forwarditerator<X>::value)>
#   define SROOK_FORWARDITER_REQUIRE_TEMPLATE_WITH_SIZE(X, S)\
    template <class X, typename S, SROOK_REQUIRES(is_forwarditerator<X>::value)>
#else
#   define SROOK_FORWARDITER_REQUIRE_TEMPLATE(X)\
    template <class X>
#   define SROOK_FORWARDITER_REQUIRE_TEMPLATE_WITH_SIZE(X, S)\
    template <class X, typename S>
#endif

SROOK_NESTED_NAMESPACE(srook, memory) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
SROOK_FORCE_INLINE void exec_destroy(T* pointer)
SROOK_NOEXCEPT(is_nothrow_destructible<T>::value)
{
    pointer->~T();
}

template <bool>
struct destroy_aux {
    SROOK_FORWARDITER_REQUIRE_TEMPLATE(ForwardIter)
    SROOK_FORCE_INLINE static void do_destroy(ForwardIter first, ForwardIter last)
    SROOK_NOEXCEPT(type_traits::detail::Land<bool_constant<noexcept(srook::memory::detail::destroy_impl(srook::addressof(*first)))>, is_nothrow_incrementable<ForwardIter>, is_nothrow_equality_comparable<ForwardIter>>::value)
    {
        for(; first != last; ++first) 
            srook::memory::detail::exec_destroy(srook::addressof(*first));
    }
};

template <>
struct destroy_aux<true> {
    SROOK_FORWARDITER_REQUIRE_TEMPLATE(ForwardIter)
    SROOK_FORCE_INLINE static void do_destroy(ForwardIter, ForwardIter) {}
};

SROOK_FORWARDITER_REQUIRE_TEMPLATE(ForwardIter)
SROOK_FORCE_INLINE void destroy_impl(ForwardIter first, ForwardIter last)
SROOK_NOEXCEPT(destroy_aux<srook::has_trivial_destructor<value_type>::value>::do_destroy(first, last))
{
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::value_type value_type;
    SROOK_ST_ASSERT(is_destructible<value_type>::value);
    destroy_aux<srook::has_trivial_destructor<value_type>::value>::do_destroy(first, last);
}

template <bool>
struct destroy_n_aux {
    SROOK_FORWARDITER_REQUIRE_TEMPLATE_WITH_SIZE(ForwardIter, Size)
    SROOK_FORCE_INLINE static ForwardIter do_destroy(ForwardIter first, Size count)
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_decrementable<Size>, 
            srook::algorithm::detail::iter_ref_apply<is_nothrow_destructible, ForwardIter>, 
            is_nothrow_incrementable<ForwardIter>, 
            is_nothrow_gt_comparable<Size>
        >::value
    )
    {
        for(; count > 0; ++first, --count)
            srook::memory::detail::exec_destroy(srook::addressof(*first));
        return first;
    }
};

template <>
struct destroy_n_aux<true> {
    SROOK_FORWARDITER_REQUIRE_TEMPLATE_WITH_SIZE(ForwardIter, Size)
    SROOK_FORCE_INLINE static ForwardIter do_destroy(ForwardIter first, Size count)
    SROOK_NOEXCEPT(srook::iterator::advance(first, count))
    {
        srook::iterator::advance(first, count);
        return first;
    }
};

SROOK_FORWARDITER_REQUIRE_TEMPLATE_WITH_SIZE(ForwardIter, Size)
SROOK_FORCE_INLINE ForwardIter destroy_n_impl(ForwardIter first, Size s)
{
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::value_type value_type;
    SROOK_ST_ASSERT(is_destructible<value_type>::value);
    return destroy_n_aux<srook::has_trivial_destructor<value_type>::value>::do_destroy(first, s);
}

#if SROOK_HAS_CONCEPTS
template <class ForwardIter, class Allocator> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class Allocator, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class Allocator>
#endif
SROOK_FORCE_INLINE void destroy_impl(ForwardIter first, ForwardIter last, Allocator& alloc)
SROOK_NOEXCEPT(type_traits::detail::Land<bool_constant<noexcept(traits_type::destroy(alloc, srook::addressof(*first)))>, is_nothrow_equality_comparable<ForwardIter>, is_nothrow_incrementable<ForwardIter>>::value)
{
    typedef std::allocator_traits<Allocator> traits_type;
    for (; first != last; ++first) traits_type::destroy(alloc, srook::addressof(*first));
}

#if SROOK_HAS_CONCEPTS
template <class ForwardIter, class T> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class T, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class T>
#endif
SROOK_FORCE_INLINE void destroy_impl(ForwardIter first, ForwardIter last, std::allocator<T>&)
SROOK_NOEXCEPT(destroy_impl(first, last))
{
    destroy_impl(first, last);
}


#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter>
#endif
SROOK_FORCE_INLINE void destroy_impl(ForwardIter iter)
SROOK_NOEXCEPT(detail::exec_destroy(iter))
{
    detail::exec_destroy(iter);
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter, class Allocator>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class Allocator, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class Allocator>
#endif
SROOK_FORCE_INLINE void destroy_impl(ForwardIter iter, Allocator alloc)
SROOK_NOEXCEPT(destroy_impl(iter, srook::next(iter), alloc))
{
    destroy_impl(iter, srook::next(iter), alloc);
}

#undef SROOK_FORWARDITER_REQUIRE_TEMPLATE
#undef SROOK_FORWARDITER_REQUIRE_TEMPLATE_WITH_SIZE
} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(memory, srook)
#endif
