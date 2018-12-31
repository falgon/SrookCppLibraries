// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_ALGORITHM_DISTANCE_HPP
#define INCLUDED_SROOK_ITERATOR_ALGORITHM_DISTANCE_HPP

#include <srook/algorithm/detail/config.hpp>
#include <srook/cxx20/concepts/iterator/InputIterator.hpp>
#include <srook/type_traits/iterator/is_inputiterator.hpp>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, iterator) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class InputIter>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::difference_type 
distance(InputIter first, InputIter last, std::input_iterator_tag tag, SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::difference_type n = 0)
SROOK_NOEXCEPT(is_nothrow_incrementable<InputIter>::value)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_InputIteratorConcept<InputIter>)
#endif
   return first == last ? n : detail::distance(++first, last, srook::move(tag), n + 1);
}

template <class RandomAccessIter>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME std::iterator_traits<RandomAccessIter>::difference_type
distance(RandomAccessIter first, RandomAccessIter last, std::random_access_iterator_tag)
SROOK_NOEXCEPT(is_nothrow_incrementable<InputIter>::value)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
    return last - first;
}

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <class InputIter> requires srook::concepts::InputIterator<InputIter> || is_pointer<InputIter>::value
#elif SROOK_HAS_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class InputIter, SROOK_REQUIRES(is_inputiterator<InputIter>::value)>
#else
template <class InputIter>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::difference_type 
distance(InputIter first, InputIter last)
SROOK_NOEXCEPT(detail::distance(first, last, SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::iterator_category()))
{
    return detail::distance(first, last, SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::iterator_category());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, srook)

namespace srook {

using srook::iterator::distance;

} // namespace srook
#endif
