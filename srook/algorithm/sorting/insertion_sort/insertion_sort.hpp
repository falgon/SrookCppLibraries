// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_INSERTION_SORT_INSERTION_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_INSERTION_SORT_INSERTION_SORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/algorithm/sorting/insertion_sort/binary_search_inserter.hpp>
#include <srook/cxx20/concepts/iterator/BidirectionalIterator.hpp>
#include <srook/type_traits/iterator/is_bidirectionaliterator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_dereferenceable.hpp>
#include <srook/type_traits/is_incrementable.hpp>
#include <srook/functional/op/deduction_less.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <class BidirectionalIter, class Compare, class SearchInserter> requires srook::concepts::BidirectionalIterator<BidirectionalIter> || is_pointer<BidirectionalIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class BidirectionalIter, class Compare, class SearchInserter, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
template <class BidirectionalIter, class Compare, class SearchInserter>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_invocable, Compare, BidirectionalIter, BidirectionalIter>::type,
        is_invocable<SearchInserter, BidirectionalIter, BidirectionalIter, Compare>
    >::value
>::type
#else
void
#endif
insertion_sort(BidirectionalIter first, BidirectionalIter last, Compare comp, SearchInserter search_inserter)
SROOK_NOEXCEPT(type_traits::detail::Land<
    is_nothrow_dereferenceable<BidirectionalIter>, 
    SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, BidirectionalIter, BidirectionalIter>::type,
    is_nothrow_invocable<SearchInserter, BidirectionalIter, BidirectionalIter, Compare>,
    is_nothrow_incrementable<BidirectionalIter>
>::value)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_BidirectionalIteratorConcept(BidirectionalIter>)
#endif
    for (BidirectionalIter i = srook::iterator::next(first); i != last; ++i) {
        if (!comp(*srook::iterator::prev(i), *i)) {
            search_inserter(first, i, comp);
        }
    }
}

#if SROOK_HAS_CONCEPTS
template <class BidirectionalIter, class Compare> requires srook::concepts::BidirectionalIterator<BidirectionalIter> || is_pointer<BidirectionalIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class BidirectionalIter, class Compare, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
template <class BidirectionalIter, class Compare>
#endif
SROOK_FORCE_INLINE void insertion_sort(BidirectionalIter first, BidirectionalIter last, Compare comp)
SROOK_NOEXCEPT(srook::algorithm::insertion_sort(first, last, comp, srook::algorithm::binary_search_inserter()))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_BidirectionalIteratorConcept<BidirectionalIter>)
#endif
    srook::algorithm::insertion_sort(first, last, comp, srook::algorithm::binary_search_inserter());
}

#if SROOK_HAS_CONCEPTS
template <class BidirectionalIter> requires srook::concepts::BidirectionalIterator<BidirectionalIter> || is_pointer<BidirectionalIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class BidirectionalIter, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
template <class BidirectionalIter>
#endif
SROOK_FORCE_INLINE void insertion_sort(BidirectionalIter first, BidirectionalIter last)
SROOK_NOEXCEPT(srook::algorithm::insertion_sort(first, last, srook::functional::deduction_less(), srook::algorithm::binary_search_inserter()))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_BidirectionalIteratorConcept<BidirectionalIter>)
#endif
    srook::algorithm::insertion_sort(first, last, srook::functional::deduction_less(), srook::algorithm::binary_search_inserter());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
