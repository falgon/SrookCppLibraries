// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_ALGORITHM_PREV_HPP
#define INCLUDED_SROOK_ITERATOR_ALGORITHM_PREV_HPP

#include <srook/iterator/range_access/advance.hpp>
#include <srook/cxx20/concepts/iterator/BidirectionalIterator.hpp>
#include <srook/type_traits/iterator/is_bidirectionaliterator.hpp>

SROOK_NESTED_NAMESPACE(srook, iterator) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <class BidirectionalIter> requires srook::concepts::BidirectionalIterator<BidirectionalIter> || is_pointer<BidirectionalIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class BidirectionalIter, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
template <class BidirectionalIter>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR BidirectionalIter prev(BidirectionalIter iter, SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::difference_type n = 1)
SROOK_NOEXCEPT(srook::iterator::algorithm::advance(iter, srook::move(n)))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_BidirectionalIteratorConcept<_BidirectionalIterator>)
#endif   
    return srook::iterator::advance(iter, -n);
}
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, srook)

namespace srook {

using srook::iterator::prev;

} // namespace srook
#endif
