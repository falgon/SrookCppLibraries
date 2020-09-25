// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_REVERSE_HPP
#define INCLUDED_SROOK_ALGORITHM_REVERSE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/cxx20/concepts/iterator/BidirectionalIterator.hpp>
#include <srook/cxx20/concepts/iterator/RandomAccessIterator.hpp>
#include <srook/type_traits/iterator/is_bidirectionaliterator.hpp>
#include <srook/type_traits/iterator/is_randomaccessiterator.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/type_traits/is_incrementable.hpp>
#include <srook/type_traits/is_decrementable.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class BidirectionalIterator>
SROOK_FORCE_INLINE BidirectionalIterator reverse_impl(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_incrementable<BidirectionalIterator>, is_nothrow_decrementable<BidirectionalIterator>, is_nothrow_equality_comparable<BidirectionalIterator>
    >::value
)
{
    while (true) {
        if (first == last || first == --last) return first;
        else {
            std::iter_swap(first, last);
            ++first;
        }
    }
    return first;
}

template <class RandomAccessIterator>
SROOK_FORCE_INLINE RandomAccessIterator reverse_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_incrementable<BidirectionalIterator>, is_nothrow_decrementable<BidirectionalIterator>, is_nothrow_equality_comparable<BidirectionalIterator>
    >::value
)
{
    if (first == last) return first;
    --last;
    while (first < last) {
        std::iter_swap(first, last);
        ++first;
        --last;
    }
    return first;
}

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <class BidirectionalIter> requires srook::concepts::BidirectionalIterator<BidirectionalIter> || is_pointer<BidirectionalIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class BidirectionalIter, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
template <class BidirectionalIter>
#endif
SROOK_FORCE_INLINE void reverse(BidirectionalIter first, BidirectionalIter last)
SROOK_NOEXCEPT(detail::reverse_impl(first, last, SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::iterator_category()))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<BidirectionalIter>)
    __glibcxx_requires_valid_range(first, last);
#endif
    detail::reverse_impl(first, last, SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::iterator_category());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
