// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_QUICK_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_QUICK_SORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/algorithm/sorting/detail/qsort_helper.hpp>
#include <srook/type_traits/iterator/is_bidirectionaliterator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/type_traits/is_dereferenceable.hpp>
#include <srook/type_traits/is_incrementable.hpp>
#include <srook/algorithm/med.hpp>
#include <srook/cxx20/concepts/iterator/BidirectionalIterator.hpp>
#include <srook/functional/op/deduction_less.hpp>
#include <srook/functional/not_fn.hpp>
#include <functional>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

class quick_sorting : protected srook::algorithm::detail::qsort_helper {
public:
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::BidirectionalIterator BidirectionalIter, class Compare>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class BidirectionalIter, class Compare, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
    template <class BidirectionalIter, class Compare>
#endif
    SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_DEDUCED_TYPENAME 
    enable_if<detail::iter_ref_apply<is_invocable, Compare, BidirectionalIter, BidirectionalIter>::type::value>::type
#else
    void
#endif
    operator()(BidirectionalIter first, BidirectionalIter last, Compare comp) const
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, BidirectionalIter>::type,
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, BidirectionalIter>::type,
            is_nothrow_incrementable<BidirectionalIter>,
            is_nothrow_dereferenceable<BidirectionalIter>
        >::value
    )
    {
        do_qsort(first, last, comp, SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::iterator_category());
    }
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::BidirectionalIterator BidirectionalIter>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class BidirectionalIter, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
    template <class BidirectionalIter>
#endif
    SROOK_FORCE_INLINE void 
    operator()(BidirectionalIter first, BidirectionalIter last) const
    SROOK_NOEXCEPT(operator()(first, last, srook::functional::deduction_less()))
    {
        operator()(first, last, srook::functional::deduction_less());
    }
private:
    template <class BidirectionalIter, class Compare>
    void do_qsort(BidirectionalIter first, BidirectionalIter last, Compare comp, std::bidirectional_iterator_tag tag) const
    {
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::difference_type diff_type;
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::value_type value_type;
        const diff_type diff = std::distance(first, last);
            
        if (diff <= 1) return;
        const value_type pivot = *std::next(first, diff >> 1);
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        const BidirectionalIter middle1 = std::partition(first, last, std::bind(comp, std::placeholders::_1, pivot));
        const BidirectionalIter middle2 = std::partition(middle1, last, std::bind(srook::functional::not_fn(comp), pivot, std::placeholders::_1));
#else
        const BidirectionalIter middle1 = std::partition(first, last, std::bind2nd(comp, pivot));
        const BidirectionalIter middle2 = std::partition(middle1, last, std::bind1st(srook::functional::not_fn(comp), pivot));
#endif
        do_qsort(first, middle1, comp, tag);
        do_qsort(middle2, last, comp, tag);
    }

    template <class RandomAccessIter, class Compare>
    void do_qsort(RandomAccessIter first, RandomAccessIter last, Compare comp, std::random_access_iterator_tag tag) const
    {
        if (last - first <= 1) return; 
        RandomAccessIter pi = first + ((last - first) >> 1);
        std::nth_element(first, pi, last, comp);
        do_qsort(first, pi, comp, tag); 
        do_qsort(pi, last, comp, tag); 
    }
};
    

#if SROOK_HAS_CONCEPTS
template <srook::concepts::BidirectionalIterator BidirectionalIter, class Compare>
#else
template <class BidirectionalIter, class Compare, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#endif
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME 
enable_if<detail::iter_ref_apply<is_invocable, Compare, BidirectionalIter, BidirectionalIter>::type::value>::type
#else
void
#endif
quick_sort(BidirectionalIter first, BidirectionalIter last, Compare comp)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, BidirectionalIter>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, BidirectionalIter>::type,
        is_nothrow_incrementable<BidirectionalIter>,
        is_nothrow_dereferenceable<BidirectionalIter>
    >::value
)
{
    srook::algorithm::quick_sorting()(first, last, comp);
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::BidirectionalIterator BidirectionalIter>
#else
template <class BidirectionalIter, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#endif
SROOK_FORCE_INLINE void quick_sort(BidirectionalIter first, BidirectionalIter last)
SROOK_NOEXCEPT(srook::algorithm::quick_sort(first, last, srook::functional::deduction_less()))
{
    srook::algorithm::quick_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
