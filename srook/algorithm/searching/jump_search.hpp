// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_JUMP_SEARCH_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_JUMP_SEARCH_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/algorithm/max.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>
#include <srook/type_traits/is_incrementable.hpp>
#include <srook/type_traits/is_decrementable.hpp>
#include <srook/math/constants/algorithm/sqrt.hpp>
#include <srook/iterator/range_access.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class ForwardIter, class T>
ForwardIter 
jump_search(ForwardIter first, ForwardIter last, const T& val, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type jump, std::forward_iterator_tag)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_incrementable<ForwardIter>, 
        is_nothrow_incrementable<SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type>,
        is_nothrow_decrementable<SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type>
    >::value
)
{
#ifdef SROOK_GCC
    __glibcxx_function_requires(_ForwardIteratorConcept<ForwardIter>)
#endif
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type diff_type;
    if (first == last) return last;

    diff_type i = 0, len = srook::iterator::distance(first, last);
    for (; i + jump < len && *srook::iterator::next(first, i) < val; i += jump);

    diff_type right = val <= *std::next(first, i) ? i : len;
    for (diff_type left = srook::algorithm::max(right - jump, diff_type(0)); right >= left; --right) {
        ForwardIter iter = std::next(first, right);
        if (*iter == val) return iter;
    }
    return last;
}

template <class ForwardIter, class T>
ForwardIter 
jump_search(ForwardIter first, ForwardIter last, const T& val, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type jump, std::random_access_iterator_tag)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_incrementable<ForwardIter>, 
        is_nothrow_incrementable<SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type>,
        is_nothrow_decrementable<SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type>
    >::value
)
{
#ifdef SROOK_GCC
    __glibcxx_function_requires(_ForwardIteratorConcept<ForwardIter>)
#endif
    if (first == last) return last;

    ForwardIter iter = first;
    for (; iter + jump < last && *(iter + jump) < val; iter += jump);
    
    if (val > *iter) iter = last - 1;
    for (ForwardIter left = iter - jump < first ? first : iter - jump; left <= iter; --iter) {
        if (*iter == val) return iter;
    }
    return last;
}

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <class ForwardIter, class T> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class T, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class T>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Lor<
        SROOK_DEDUCED_TYPENAME srook::algorithm::detail::iter_ref_apply<is_convertible, ForwardIter, T>::type, 
        SROOK_DEDUCED_TYPENAME srook::algorithm::detail::iter_ref_apply<is_convertible, T, ForwardIter>::type
    >::value,
    ForwardIter
>::type
#else
ForwardIter
#endif
jump_search(ForwardIter first, ForwardIter last, const T& val, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type jump)
SROOK_NOEXCEPT(is_nothrow_incrementable<ForwardIter>::value)
{
#ifdef SROOK_GCC
    __glibcxx_function_requires(_ForwardIteratorConcept<ForwardIter>)
#endif
    return srook::algorithm::detail::jump_search(first, last, val, srook::move(jump), SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::iterator_category());
}

#if SROOK_HAS_CONCEPTS
template <class ForwardIter, class T> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, class T, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter, class T>
#endif
SROOK_FORCE_INLINE ForwardIter
jump_search(ForwardIter first, ForwardIter last, const T& val)
SROOK_NOEXCEPT(srook::algorithm::jump_search(first, last, val, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type()))
{
    return srook::algorithm::jump_search(
        first, last, val, 
        static_cast<SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type>(srook::math::sqrt(srook::iterator::distance(first, last)))
    );
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
