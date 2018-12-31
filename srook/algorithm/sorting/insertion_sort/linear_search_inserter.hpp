// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_INSERTION_SORT_LINEAR_SEARCH_INSERT_HPP
#define INCLUDED_SROOK_ALGORITHM_INSERTION_SORT_LINEAR_SEARCH_INSERT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/rotate.hpp>
#include <srook/algorithm/detail/config.hpp>
#include <srook/algorithm/searching/upper_bound.hpp>
#include <srook/cxx20/concepts/iterator/BidirectionalIterator.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

struct linear_search_inserter {
#if SROOK_HAS_CONCEPTS
    template <class BidirectionalIter, class Compare> requires srook::concepts::BidirectionalIterator<BidirectionalIter> || is_pointer<BidirectionalIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class BidirectionalIter, class Compare, SROOK_REQUIRES(is_forwarditerator<BidirectionalIter>::value)>
#else
    template <class BidirectionalIter, class Compare>
#endif
    SROOK_FORCE_INLINE void operator()(BidirectionalIter first, BidirectionalIter iter, Compare comp) const
    SROOK_NOEXCEPT()
    {
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::value_type value_type;
        const value_type x = *iter;
        do {
            *iter = *srook::iterator::next(iter, -1);
            srook::iterator::advance(iter, -1);
        } while (!comp(iter, first) && !comp(*srook::iterator::next(iter, -1), x));
        *iter = x;
    }
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
