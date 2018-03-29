// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_COUNTING_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_COUNTING_SORT_HPP

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
counting_sort(ForwardIter first, ForwardIter last, Compare comp)
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

    const std::pair<ForwardIter, ForwardIter> minmax = std::minmax_element(first, last);
    if (*minmax.first == *minmax.second) return;
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::value_type value_type;
    value_type min = *minmax.first, max = *minmax.second;

    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type diff_type;
    typedef std::vector<diff_type> counts_buffer;
    typedef SROOK_DEDUCED_TYPENAME std::vector<diff_type>::iterator counts_iter;

    counts_buffer counts(max - min + 1, 0);
    for (ForwardIter iter = first; iter != last; ++iter) ++counts[*iter - min];
    for (counts_iter iter = srook::begin(counts); iter != srook::end(counts); ++iter) first = std::fill_n(first, *iter, min++);    
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter>
#else
template <class ForwardIter, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#endif
SROOK_FORCE_INLINE void counting_sort(ForwardIter first, ForwardIter last)
SROOK_NOEXCEPT(srook::algorithm::counting_sort(first, last, srook::functional::deduction_less()))
{
    srook::algorithm::counting_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
