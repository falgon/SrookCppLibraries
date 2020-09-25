// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SHAKER_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_SHAKER_SORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/type_traits/is_dereferenceable.hpp>
#include <srook/type_traits/is_incrementable.hpp>
#include <srook/cxx20/concepts/iterator/BidirectionalIterator.hpp>
#include <srook/functional/op/deduction_less.hpp>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <srook::concepts::BidirectionalIterator BidirectionalIter, class Compare>
#else
template <class BidirectionalIter, class Compare, SROOK_REQUIRES(is_forwarditerator<BidirectionalIter>::value)>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME 
enable_if<detail::iter_ref_apply<is_invocable, Compare, BidirectionalIter, BidirectionalIter>::type::value>::type
#else
void
#endif
shaker_sort(BidirectionalIter first, BidirectionalIter last, Compare comp)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, BidirectionalIter>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, BidirectionalIter>::type,
        is_nothrow_incrementable<BidirectionalIter>,
        is_nothrow_dereferenceable<BidirectionalIter>
    >::value
)
{
    if (first == last) return;
    
    BidirectionalIter end = srook::iterator::prev(last);
    for (BidirectionalIter t = last; first != last;) {
        for (BidirectionalIter iter = first; iter != end; ++iter) {
            BidirectionalIter next = srook::iterator::next(iter);
            if (comp(*next, *iter)) {
                std::iter_swap(next, iter);
                t = iter;
            }
        }
        last = t;
        if (first == last) break;
        for (BidirectionalIter iter = last; iter != first; --iter) {
            BidirectionalIter prev = srook::iterator::prev(iter);
            if (comp(*iter, *prev)) {
                std::iter_swap(prev, iter);
                t = iter;
            }
        }
        first = t;
    }
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::BidirectionalIterator BidirectionalIter>
#else
template <class BidirectionalIter, SROOK_REQUIRES(is_forwarditerator<BidirectionalIter>::value)>
#endif
SROOK_FORCE_INLINE void shaker_sort(BidirectionalIter first, BidirectionalIter last)
SROOK_NOEXCEPT(srook::algorithm::shaker_sort(first, last, srook::functional::deduction_less()))
{
    srook::algorithm::shaker_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
