// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_ALGORITHM_NEXT_HPP
#define INCLUDED_SROOK_ITERATOR_ALGORITHM_NEXT_HPP

#include <srook/iterator/range_access/advance.hpp>
#include <srook/cxx20/concepts/iterator/InputIterator.hpp>
#include <srook/type_traits/iterator/is_inputiterator.hpp>

SROOK_NESTED_NAMESPACE(srook, iterator) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <class InputIter> requires srook::concepts::InputIterator<InputIter> || is_pointer<InputIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class InputIter, SROOK_REQUIRES(is_inputiterator<InputIter>::value)>
#else
template <class InputIter>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR InputIter next(InputIter iter, SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::difference_type n = 1)
SROOK_NOEXCEPT(srook::iterator::algorithm::advance(iter, srook::move(n)))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
#endif   
    return srook::iterator::advance(iter, srook::move(n));
}
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, srook)

namespace srook {

using srook::iterator::next;

} // namespace srook

#endif
