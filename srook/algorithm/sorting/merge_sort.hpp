// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_MERGE_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_MERGE_SORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/algorithm/inplace_merge.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <class RandomAccessIter, class Compare> requires srook::concepts::RandomAccessIterator<RandomAccessIter> || is_pointer<RandomAccessIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class RandomAccessIter, class Compare, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
template <class RandomAccessIter, class Compare>
#endif
void merge_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
SROOK_NOEXCEPT(srook::algorithm::inplace_merge(first, first, last, comp))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<RandomAccessIter>::difference_type diff_type;
    const diff_type diff = srook::iterator::distance(last, first);
    if (last - first > 1) {
        RandomAccessIter middle = first + ((last - first) >> 1);
        merge_sort(first, middle, comp);
        merge_sort(middle, last, comp);
        srook::algorithm::inplace_merge(first, middle, last, comp);
    }
}

#if SROOK_HAS_CONCEPTS
template <class RandomAccessIter> requires srook::concepts::RandomAccessIterator<RandomAccessIter> || is_pointer<RandomAccessIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class RandomAccessIter, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
template <class RandomAccessIter>
#endif
SROOK_FORCE_INLINE void merge_sort(RandomAccessIter first, RandomAccessIter last)
SROOK_NOEXCEPT(srook::algorithm::merge_sort(first, last, srook::functional::deduction_less()))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
    return srook::algorithm::merge_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
