// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_BINARY_SEARCH_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_BINARY_SEARCH_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/searching/lower_bound.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <class ForwardIter, class T, class Compare> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class T, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class T, class Compare>
#endif
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME enable_if<detail::iter_ref_apply<is_invocable, Compare, T, ForwardIter>::value, bool>::type
#else
bool
#endif
binary_search(ForwardIter first, ForwardIter last, const T& val, Compare comp)
SROOK_NOEXCEPT(is_nothrow_dereferenceable<ForwardIter>::value)
{
    ForwardIter iter = srook::algorithm::lower_bound(first, last, val, comp);
    return iter != last && !comp(val, *iter);
}

#if SROOK_HAS_CONCEPTS
template <class ForwardIter, class T, class Compare> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS => SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class T, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class T, class Compare>
#endif
bool binary_search(ForwardIter first, ForwardIter last, const T& val)
SROOK_NOEXCEPT(srook::algorithm::binary_search(first, last, val, srook::functional::deduction_less()))
{
    return srook::algorithm::binary_search(first, last, val, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
