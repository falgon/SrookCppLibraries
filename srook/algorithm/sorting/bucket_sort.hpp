// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_BUCKET_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_BUCKET_SORT_HPP

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
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/functional/op/deduction_less.hpp>
#include <srook/numeric/algorithm/iota.hpp>
#include <vector>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter, class Compare>
#else
template <class ForwardIter, class Compare, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_invocable, Compare, ForwardIter, ForwardIter>::type,
        is_integral<SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::value_type>
    >::value
>::type
#else
void
#endif
bucket_sort(ForwardIter first, ForwardIter last, Compare comp)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, ForwardIter>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, ForwardIter>::type,
        is_nothrow_incrementable<ForwardIter>,
        is_nothrow_dereferenceable<ForwardIter>
    >::value
)
{
    if (first == last || srook::iterator::next(first) == last) return;
    
    std::vector<int> buckets(srook::iterator::distance(first, last), 0);
    for (ForwardIter iter = first; iter != last; ++iter) buckets[*iter] = *iter;
    for (std::size_t i = 0; i < buckets.size(); ++i) *first++ = buckets[i];
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter>
#else
template <class ForwardIter, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#endif
SROOK_FORCE_INLINE void bucket_sort(ForwardIter first, ForwardIter last)
SROOK_NOEXCEPT(srook::algorithm::bucket_sort(first, last, srook::functional::deduction_less()))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_ForwardIteratorConcept<ForwardIter>)
#endif
    srook::algorithm::bucket_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
