// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_ODD_EVEN_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_ODD_EVEN_SORT_HPP

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
odd_even_sort(BidirectionalIter first, BidirectionalIter last, Compare comp)
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
    bool b = false;
    BidirectionalIter end = srook::iterator::prev(last);
    do {
        b = false;
        for (BidirectionalIter iter = first; iter < end; srook::iterator::advance(iter, 2)) {
            BidirectionalIter next = srook::iterator::next(iter);
            if (comp(*next, *iter)) {
                std::iter_swap(iter, next);
                b = true;
            }
        }
        for (BidirectionalIter iter = srook::iterator::next(first); iter < end; srook::iterator::advance(iter, 2)) {
            BidirectionalIter next = srook::iterator::next(iter);
            if (comp(*next, *iter)) {
                std::iter_swap(iter, next);
                b = true;
            }
        }
    } while (b);
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::BidirectionalIterator BidirectionalIter>
#else
template <class BidirectionalIter, SROOK_REQUIRES(is_forwarditerator<BidirectionalIter>::value)>
#endif
SROOK_FORCE_INLINE void odd_even_sort(BidirectionalIter first, BidirectionalIter last)
SROOK_NOEXCEPT(srook::algorithm::odd_even_sort(first, last, srook::functional::deduction_less()))
{
    srook::algorithm::odd_even_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
