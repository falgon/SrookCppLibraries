// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_ALGORITHM_ADVANCE_HPP
#define INCLUDED_SROOK_ITERATOR_ALGORITHM_ADVANCE_HPP

#include <srook/iterator/range_access/distance.hpp>


SROOK_NESTED_NAMESPACE(srook, iterator) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class InputIter, class Distance>
SROOK_CONSTEXPR InputIter 
advance(InputIter& iter, Distance n, std::input_iterator_tag tag)
SROOK_NOEXCEPT(is_nothrow_incrementable<InputIter>::value)
{
    assert(n >= 0);
    return !n ? iter : detail::advance(++iter, n - 1, srook::move(tag));
}

template <class BidirectionalIter, class Distance>
SROOK_CONSTEXPR BidirectionalIter
advance(BidirectionalIter& iter, Distance n, std::bidirectional_iterator_tag tag)
SROOK_NOEXCEPT(is_nothrow_incrementable<InputIter>::value)
{
    return n > 0 ? detail::advance(++iter, n - 1, srook::move(tag)) : !n ? iter : detail::advance(--iter, n + 1, srook::move(tag));
}


template <class RandomAccessIter, class Distance>
SROOK_FORCE_INLINE SROOK_CONSTEXPR RandomAccessIter
advance(RandomAccessIter& iter, Distance n, std::random_access_iterator_tag)
SROOK_NOEXCEPT(is_nothrow_incrementable<InputIter>::value)
{
#ifdef __GNU_LIBRARY__
    return __builtin_constant_p(n) && n == static_cast<Distance>(1) ? ++iter : __builtin_constant_p(n) && n == static_cast<Distance>(-1) ? --iter : iter += n;
#else
    return iter += n;
#endif
}

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <class InputIter, class Distance> requires srook::concepts::InputIterator<InputIter> || is_pointer<InputIter>::value
#elif SROOK_HAS_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class InputIter, class Distance, SROOK_REQUIRES(is_inputiterator<InputIter>::value)>
#else
template <class InputIter, class Distance>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR InputIter
advance(InputIter& iter, Distance n)
SROOK_NOEXCEPT(detail::advance(iter, srook::move(n), SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::iterator_category()))
{
    return detail::advance(iter, srook::move(n), SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::iterator_category());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, srook)

namespace srook {

using srook::iterator::advance;

} // namespace srook
#endif
