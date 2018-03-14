// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_LOWER_BOUND_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_LOWER_BOUND_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/functional/op/deduction_less.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>
#include <srook/type_traits/is_dereferenceable.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/iterator/range_access.hpp>

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
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_invocable, Compare, ForwardIter, T>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_convertible, ForwardIter, T>::type
    >::value,
    ForwardIter
>::type
#else
ForwardIter
#endif
lower_bound(ForwardIter first, ForwardIter last, const T& val, Compare comp)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_dereferenceable<ForwardIter>, SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, ForwardIter, T>::type>::value)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_ForwardIteratorConcept<ForwardIter>)
    __glibcxx_function_requires(_BinaryPredicateConcept<Compare, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::value_type, _Tp>)
    __glibcxx_requires_partitioned_lower_pred(first, last, val, comp);
#endif
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type diff_type;

    for (diff_type len = srook::iterator::distance(first, last); len > 0;) {
        diff_type half = len >> 1;
        ForwardIter mid = first;
        srook::advance(mid, half);

        if (comp(*mid, val)) {
            first = mid;
            ++first;
            len -= half - 1;
        } else {
            len = half;
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
ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T& val)
SROOK_NOEXCEPT(lower_bound(first, last, val, srook::functional::deduction_less()))
{
    return srook::algorithm::lower_bound(first, last, val, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
