// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SELECTION_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_SELECTION_SORT_HPP

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
#include <srook/iterator/range_access.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/functional/op/deduction_less.hpp>
#include <srook/cstdint.hpp>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class ForwardIter, class Compare>
void selection_sort_impl(ForwardIter first, ForwardIter last, Compare comp)
{
    for (ForwardIter iter = first; iter != last; ++iter) std::iter_swap(iter, std::min_element(iter, last, comp));
}

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter, class Compare>
#else
template <class ForwardIter, class Compare, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME 
enable_if<detail::iter_ref_apply<is_invocable, Compare, ForwardIter, ForwardIter>::type::value>::type
#else
void
#endif
selection_sort(ForwardIter first, ForwardIter last, Compare comp)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, ForwardIter>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, ForwardIter>::type,
        is_nothrow_incrementable<ForwardIter>,
        is_nothrow_dereferenceable<ForwardIter>
    >::value
)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_ForwardIteratorConcept<ForwardIter>)
#endif
    srook::algorithm::detail::selection_sort_impl(first, last, srook::move(comp));
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter>
#else
template <class ForwardIter, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#endif
SROOK_FORCE_INLINE void selection_sort(ForwardIter first, ForwardIter last)
SROOK_NOEXCEPT(srook::algorithm::selection_sort(first, last, srook::functional::deduction_less()))
{
    srook::algorithm::selection_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
