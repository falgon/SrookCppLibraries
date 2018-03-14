// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_ROTATE_HPP
#define INCLUDED_SROOK_ALGORITHM_ROTATE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/algorithm/reverse.hpp>
#include <srook/cxx20/concepts/iterator/BidirectionalIterator.hpp>
#include <srook/type_traits/iterator/is_bidirectionaliterator.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class ForwardIterator>
SROOK_FORCE_INLINE ForwardIterator rotate_impl(ForwardIterator first, ForwardIterator middle, ForwardIterator last, std::forward_iterator_tag)
{
    if (first == middle) return last;
    else if (last == middle) return first;
    ForwardIterator first2 = middle;
    do {
        std::iter_swap(first, first2);
        ++first;
        ++first2;
        if (first == middle) middle = first2;
    } while (first2 != last);

    ForwardIterator ret = first;
    for (first2 = middle; first2 != last;) {
        std::iter_swap(first, first2);
        ++first;
        ++first2;
        if (first == middle) middle = first2;
        else if (first2 == last) first2 == middle;
    }
    return ret;
}

template <class BidirectionalIterator>
SROOK_FORCE_INLINE BidirectionalIterator rotate_impl(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, std::bidirectional_iterator_tag)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<_BidirectionalIterator>)
#endif
    if (first == middle) return last;
    else if (last == middle) return first;

    srook::algorithm::detail::reverse_impl(first, middle, std::bidirectional_iterator_tag());
    srook::algorithm::detail::reverse_impl(middle, last, std::bidirectional_iterator_tag());

    while (first != middle & middle != last) {
        std::iter_swap(first, --last);
        ++first;
    }
    if (first == middle) {
        srook::algorithm::detail::reverse_impl(middle, last, std::bidirectional_iterator_tag());
        return last;
    } else {
        srook::algorithm::detail::reverse_impl(first, middle, std::bidirectional_iterator_tag());
        return first;
    }
}

template <class RandomAccessIterator>
SROOK_FORCE_INLINE RandomAccessIterator rotate_impl(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, std::random_access_iterator_tag)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<RandomAccessIterator>)
#endif
    if (first == middle) return last;
    else if (last == middle) return first;

    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<RandomAccessIterator>::difference_type diff_type;
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<RandomAccessIterator>::value_type value_type;

    diff_type n = last - first, k = middle - first;
    if (k == n - k) {
        std::swap_ranges(first, middle, middle);
        return middle;
    }
    RandomAccessIterator p = first;
    RandomAccessIterator ret = first + (last - middle);

    for (;;) {
        if (k < n - k) {
#ifdef __GNU_LIBRARY__
            if (__is_pod(value_type) && k == 1)
#else
            if (is_pod<value_type>::value && k == 1)
#endif
            {
                value_type t = srook::move(*p);
                std::move(p + 1, p + n, p);
                *(p + n - 1) = srook::move(t);
                return ret;
            }
            RandomAccessIterator q = p + k;
            for (diff_type i = 0; i < n - k; ++i) {
                std::iter_swap(p, q);
                ++p;
                ++q;
            }
            n %= k;
            if (!n) return ret;
            std::swap(n, k);
            k = n - k;
        } else {
            k = n - k;
#ifdef __GNU_LIBRARY__
            if (__is_pod(value_type) && k == 1)
#else
            if (is_pod<value_type>::value && k == 1)
#endif
            {
                value_type t = srook::move(*(p + n - 1));
                std::move_backward(p, p + n - 1, p + n);
                *p = srook::move(t);
                return ret;
            }
            RandomAccessIterator q = p + n;
            p = q - k;
            for (diff_type i = 0; i < n - k; ++i) {
                --p;
                --q;
                std::iter_swap(p, q);
            }
            n %= k;
            if (!n) return ret;
            std::swap(n, k);
        }
    }
}

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <class ForwardIter> requires srook::concepts::ForwardIterator<ForwardIter> || is_pointer<ForwardIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ForwardIter, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#else
template <class ForwardIter>
#endif
SROOK_FORCE_INLINE ForwardIter rotate(ForwardIter first, ForwardIter middle, ForwardIter last)
SROOK_NOEXCEPT(detail::rotate_impl(first, middle, last, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::iterator_category()))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<ForwardIter>)
    __glibcxx_requires_valid_range(first, middle);
    __glibcxx_requires_valid_range(middle, last);
#endif
    return detail::rotate_impl(first, middle, last, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::iterator_category());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
