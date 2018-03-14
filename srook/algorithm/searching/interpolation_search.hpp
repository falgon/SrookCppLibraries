// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_INTERPOLATION_SEARCH_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_INTERPOLATION_SEARCH_HPP

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
template <class ForwardIter, class T, class Compare SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class T, class Compare>
#endif
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME srook::algorithm::detail::iter_ref_apply<is_invocable, Compare, ForwardIter, T>::type,
        type_traits::detail::Lor<
            SROOK_DEDUCED_TYPENAME srook::algorithm::detail::iter_ref_apply<is_convertible, ForwardIter, T>::type, 
            SROOK_DEDUCED_TYPENAME srook::algorithm::detail::iter_ref_apply<is_convertible, T, ForwardIter>::type
        >
    >::value,
    ForwardIter
>::type
#else
ForwardIter
#endif
interpolation_search(ForwardIter first, ForwardIter last, const T& val, Compare comp)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_incrementable<ForwardIter>, SROOK_DEDUCED_TYPENAME srook::algorithm::detail::iter_ref_apply<is_nothrow_invocable, ForwardIter, T>::type>::value)
{
#ifdef SROOK_GCC
    __glibcxx_function_requires(_ForwardIteratorConcept<ForwardIter>)
    __glibcxx_function_requires(_BinaryPredicateConcept<Compare, T, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::value_type>)
    __glibcxx_requires_partitioned_upper_pred(first, last, val, comp);
#endif
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type diff_type;
    if (first == last) return last;
    
    for (diff_type left = 0, right = srook::iterator::distance(first, last), len = right; len > 0;) {
        const diff_type half = left + (val - *srook::iterator::next(first, left)) * (right - left) / (*srook::next(first, right) - *srook::next(first, left));  //len >> 1;
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
interpolation_search(ForwardIter first, ForwardIter last, const T& val)
SROOK_NOEXCEPT(srook::algorithm::interpolation_search(first, last, val, srook::functional::deduction_less()))
{
    return srook::algorithm::interpolation_search(first, last, val, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
