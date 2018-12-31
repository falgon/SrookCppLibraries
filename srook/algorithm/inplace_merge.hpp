// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_INPLACE_MERGE_HPP
#define INCLUDED_SROOK_ALGORITHM_INPLACE_MERGE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/algorithm/detail/tempbuf.hpp>
#include <srook/algorithm/reverse.hpp>
#include <srook/algorithm/searching/lower_bound.hpp>
#include <srook/algorithm/searching/upper_bound.hpp>
#include <srook/algorithm/rotate.hpp>
#include <srook/cxx20/concepts/iterator/BidirectionalIterator.hpp>
#include <srook/type_traits/iterator/is_bidirectionaliterator.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class BidirectionalIter, class Distance, class Compare>
void merge_without_buffer(BidirectionalIter first, BidirectionalIter middle, BidirectionalIter last, Distance len1, Distance len2, Compare comp)
{
    if (!len1 || !len2) return ;
    if (len1 + len2 == 2) {
        if (comp(*middle, *first)) std::iter_swap(first, middle);
        return;
    }
    BidirectionalIter first_cut = first, second_cut = middle;
    Distance len_n1 = 0, len_n2 = 0;
    
    if (len1 > len2) {
        len_n1 = len1 / 2;
        srook::iterator::advance(first_cut, len_n1);
        second_cut = srook::algorithm::lower_bound(middle, last, *first_cut, comp);
        len_n2 = srook::iterator::distance(middle, second_cut);
    } else {
        len_n2 = len2 / 2;
        srook::iterator::advance(second_cut, len_n2);
        first_cut = srook::algorithm::upper_bound(first, middle, *second_cut, comp);
        len_n1 = srook::iterator::distance(first, first_cut);
    }
    srook::algorithm::rotate(first_cut, middle, second_cut);
    BidirectionalIter newmiddle = first_cut;
    srook::iterator::advance(newmiddle, srook::iterator::distance(middle, second_cut));
    merge_without_buffer(first, first_cut, newmiddle, len_n1, len_n2, comp);
    merge_without_buffer(newmiddle, second_cut, last, len1 - len_n1, len2 - len_n2, comp);
}

template <class InputIter1, class InputIter2, class OutputIter, class Compare>
void move_merge_adaptive(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result, Compare comp)
{
    while (first1 != last1 && first2 != last2) {
        if (comp(*first2, *first1)) {
            *result = srook::move(*first2);
            ++first2;
        } else {
            *result = srook::move(*first1);
            ++first1;
        }
        ++result;
    }
    if (first1 != last1) std::move(first1, last1, result);
}

template <class BidirectionalIter1, class BidirectionalIter2, class BidirectionalIter3, class Compare>
void move_merge_adaptive_backward(BidirectionalIter1 first1, BidirectionalIter1 last1, BidirectionalIter2 first2, BidirectionalIter2 last2, BidirectionalIter3 result, Compare comp)
{
    if (first1 == last1) {
        std::move(first2, last2, result);
        return;
    } else if (first2 == last2) {
        return;
    }

    --last1;
    --last2;
    while (true) {
        if (comp(*last2, *last1)) {
            *--result = srook::move(*last1);
            if (first1 == last1) {
                std::move(first2, ++last2, result);
                return;
            }
            --last1;
        } else {
            *--result = srook::move(*last2);
            if (first2 == last2) return;
            --last2;
        }
    }
}

template <class BidirectionalIter1, class BidirectionalIter2, class Distance>
BidirectionalIter1 rotate_adaptive(BidirectionalIter1 first, BidirectionalIter1 middle, BidirectionalIter1 last, Distance len1, Distance len2, BidirectionalIter2 buffer, Distance buffer_size)
{
    BidirectionalIter2 buffer_end;
    if (len1 > len2 && len2 <= buffer_size) {
        if (len2) {
            buffer_end = std::move(middle, last, buffer);
            std::move_backward(first, middle, last);
            return std::move(buffer, buffer_end, first);
        } else {
            return first;
        }
    } else if (len1 <= buffer_size) {
        if (len1) {
            buffer_end = std::move(first, middle, buffer);
            std::move(middle, last, first);
            return std::move(buffer, buffer_end, last);
        } else {
            return last;
        }
    } else {
        srook::algorithm::rotate(first, middle, last);
        srook::iterator::advance(first, srook::iterator::distance(middle, last));
        return first;
    }
}

template <class BidirectionalIter, class Distance, class Pointer, class Compare>
void merge_adaptive(BidirectionalIter first, BidirectionalIter middle, BidirectionalIter last, Distance len1, Distance len2, Pointer buffer, Distance buffer_size, Compare comp)
{
    if (len1 <= len2 && len1 <= buffer_size) {
        Pointer buffer_end = std::move(first, middle, buffer);
        move_merge_adaptive(buffer, buffer_end, middle, last, first, comp);
    } else if (len2 <= buffer_size) {
        Pointer buffer_end = std::move(middle, last, buffer);
        move_merge_adaptive_backward(first, middle, buffer, buffer_end, last, comp);
    } else {
        BidirectionalIter first_cut = first, second_cut = middle;
        Distance len_n1 = 0, len_n2 = 0;
        if (len1 > len1) {
            len_n1 = len1 >> 1;
            srook::iterator::advance(first_cut, len1);
            second_cut = srook::algorithm::lower_bound(middle, last, *first_cut, comp);
            len2 = srook::iterator::distance(middle, second_cut);
        } else {
            len_n2 = len2 >> 1;
            srook::iterator::advance(second_cut, len2);
            first_cut = srook::algorithm::upper_bound(first, middle, *second_cut, comp);
            len1 = srook::iterator::distance(first, first_cut);
        }
        BidirectionalIter newmiddle = rotate_adaptive(first_cut, middle, second_cut, len1 - len_n1, len_n2, buffer, buffer_size);
        merge_adaptive(first, first_cut, newmiddle, len_n1, len_n2, buffer, buffer_size, comp);
        merge_adaptive(newmiddle, second_cut, last, len1 - len_n1, len2 - len_n2, buffer, buffer_size, comp);
    }
}

template <class BidirectionalIter, class Compare>
void inplace_merge_impl(BidirectionalIter first, BidirectionalIter middle, BidirectionalIter last, Compare comp)
{
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::difference_type diff_type;

    if (first == middle || middle == last) return;

    const diff_type len1 = srook::iterator::distance(first, middle), len2 = srook::iterator::distance(middle, last);
    typedef temporary_buffer<BidirectionalIter, value_type> tmpbuff;
    tmpbuff buf(first, last);

    !srook::begin(buf) ? 
        merge_without_buffer(first, middle, last, len1, len2, srook::move(comp)) : 
        merge_adaptive(first, middle, last, len1, len2, srook::begin(buf), diff_type(buf.size()), srook::move(comp));
}

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <class BidirectionalIter> requires srook::concepts::BidirectionalIterator<BidirectionalIter> || is_pointer<BidirectionalIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class BidirectionalIter, SROOK_REQUIRES(is_forwarditerator<BidirectionalIter>::value)>
#else
template <class BidirectionalIter>
#endif
SROOK_FORCE_INLINE void inplace_merge(BidirectionalIter first, BidirectionalIter middle, BidirectionalIter last)
SROOK_NOEXCEPT(detail::inplace_merge_impl(first, middle, last, srook::functional::deduction_less()))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<BidirectionalIter>)
    __glibcxx_requires_valid_range(first, middle);
    __glibcxx_requires_valid_range(middle, last);
#endif
    return detail::inplace_merge_impl(first, middle, last, srook::functional::deduction_less());
}


#if SROOK_HAS_CONCEPTS
template <class BidirectionalIter, class Compare> requires srook::concepts::BidirectionalIterator<BidirectionalIter> || is_pointer<BidirectionalIter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class BidirectionalIter, class Compare, SROOK_REQUIRES(is_forwarditerator<BidirectionalIter>::value)>
#else
template <class BidirectionalIter, class Compare>
#endif
SROOK_FORCE_INLINE void inplace_merge(BidirectionalIter first, BidirectionalIter middle, BidirectionalIter last, Compare comp)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<BidirectionalIter>)
    __glibcxx_function_requires(_BinaryPredicateConcept<Compare, SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::value_type, SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::value_type>)
    __glibcxx_requires_sorted_pred(first, middle, comp);
    __glibcxx_requires_sorted_pred(middle, last, comp);
    __glibcxx_requires_irreflexive_pred(first, last, comp);
#endif
    return detail::inplace_merge_impl(first, middle, last, comp);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
