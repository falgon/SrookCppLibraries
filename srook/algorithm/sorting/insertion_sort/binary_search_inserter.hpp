// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_INSERTION_SORT_BINARY_SEARCH_INSERT_HPP
#define INCLUDED_SROOK_ALGORITHM_INSERTION_SORT_BINARY_SEARCH_INSERT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/rotate.hpp>
#include <srook/algorithm/detail/config.hpp>
#include <srook/algorithm/searching/upper_bound.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

struct binary_search_inserter {
#if SROOK_HAS_CONCEPTS
    template <class ForwardIter, class Compare> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class ForwardIter, class Compare, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
    template <class ForwardIter, class Compare>
#endif
    SROOK_FORCE_INLINE void operator()(ForwardIter first, ForwardIter iter, Compare comp) const
    SROOK_NOEXCEPT(srook::algorithm::rotate(srook::algorithm::upper_bound(first, iter, *iter, comp), iter, srook::next(iter, 1)))
    {
        srook::algorithm::rotate(srook::algorithm::upper_bound(first, iter, *iter, comp), iter, srook::iterator::next(iter, 1));
    }
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
