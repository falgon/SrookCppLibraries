// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_HEAP_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_HEAP_SORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/cxx20/concepts/iterator/RandomAccessIterator.hpp>
#include <srook/functional/op/deduction_less.hpp>
#include <algorithm>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <class RandomAccessIter, class Compare> requires srook::concepts::RandomAccessIterator<RandomAccessIter> || is_pointer<RandomAccessIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class RandomAccessIter, class Compare, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
template <class RandomAccessIter, class Compare>
#endif
SROOK_FORCE_INLINE void heap_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
SROOK_NOEXCEPT(type_traits::detail::Land<bool_constant<noexcept(std::make_heap(first, last, comp))>, bool_constant<noexcept(std::sort_heap(first, last, comp))>>::value)
{
    std::make_heap(first, last, comp), std::sort_heap(first, last, comp);
}

#if SROOK_HAS_CONCEPTS
template <class RandomAccessIter> requires srook::concepts::RandomAccessIterator<RandomAccessIter> || is_pointer<RandomAccessIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class RandomAccessIter, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
template <class RandomAccessIter>
#endif
SROOK_FORCE_INLINE void heap_sort(RandomAccessIter first, RandomAccessIter last)
SROOK_NOEXCEPT(srook::algorithm::heap_sort(first, last, srook::functional::deduction_less()))
{
    return srook::algorithm::heap_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
