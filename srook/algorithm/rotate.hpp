// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_ROTATE_HPP
#define INCLUDED_SROOK_ALGORITHM_ROTATE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/algorithm/iter_swap.hpp>
#include <srook/cxx20/concepts/Swappable.hpp>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <srook::algorithm::detail::SwappableAndForwardIter ForwardIter>
#else
template <class ForwardIter>
#endif
SROOK_CXX14_CONSTEXPR ForwardIter rotate(ForwardIter first, ForwardIter n_first, ForwardIter last)
{
    if (first == n_first) return last;
    if (n_first == last) return first;

    ForwardIter next = n_first;
    do {
        srook::algorithm::iter_swap(first++, next++);
        if (first == n_first) n_first = next;
    } while (next != last);

    ForwardIter ret = first;
    for (next = n_first; next != last;) {
        srook::algorithm::iter_swap(first++, next++);
        if (first == n_first) n_first = next;
        else if (next == last) next = n_first;
    }
    return ret;
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
