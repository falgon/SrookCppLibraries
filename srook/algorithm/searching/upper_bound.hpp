// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_UPPER_BOUND_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_UPPER_BOUND_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/functional/op/deduction_less.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <class ForwardIter, class T, class Compare> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class T, class Compare, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class T, class Compare>
#endif
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME enable_if<srook::algorithm::detail::iter_ref_apply<is_invocable, Compare, ForwardIter, T>::type::value, ForwardIter>::type
#else
ForwardIter
#endif
upper_bound(ForwardIter first, ForwardIter last, const T& val, Compare comp)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_incrementable<ForwardIter>, SROOK_DEDUCED_TYPENAME srook::algorithm::detail::iter_ref_apply<is_nothrow_invocable, ForwardIter, T>::type>::value)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_ForwardIteratorConcept<ForwardIter>)
    __glibcxx_function_requires(_BinaryPredicateConcept<Compare, T, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::value_type>)
    __glibcxx_requires_partitioned_upper_pred(first, last, val, comp);
#endif
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type diff_type;
    for (diff_type len = srook::iterator::distance(first, last); len > 0;) {
        const diff_type half = len >> 1;
        ForwardIter middle = first;
        srook::iterator::advance(middle, half);
        if (comp(val, *middle)) len = half;
        else {
            first = middle;
            ++first;
            len = len - half - 1;
        }
    }
    return first;
}

#if SROOK_HAS_CONCEPTS
template <class ForwardIter, class T> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class T, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class T>
#endif
SROOK_FORCE_INLINE ForwardIter
upper_bound(ForwardIter first, ForwardIter last, const T& val)
SROOK_NOEXCEPT(srook::algorithm::upper_bound(first, last, val, srook::functional::deduction_less()))
{
    return srook::algorithm::upper_bound(first, last, val, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
