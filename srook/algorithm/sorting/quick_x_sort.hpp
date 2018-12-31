// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_QUICK_X_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_QUICK_X_SORT_HPP

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

class quick_x_sorting : protected srook::algorithm::detail::qsort_helper {
public:
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::BidirectionalIterator BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2, class Compare>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2, class Compare, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
    template <class BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2, class Compare>
#endif
    SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_DEDUCED_TYPENAME 
    enable_if<
        type_traits::detail::Land<
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_invocable, Compare, BidirectionalIter, BidirectionalIter>::type,
            is_invocable<Fn1, BidirectionalIter, BidirectionalIter, Compare>,
            is_invocable<Fn2, BidirectionalIter, BidirectionalIter, Compare>,
            is_integral<Integral1>,
            is_integral<Integral2>
        >::value
    >::type
#else
    void
#endif
    operator()(BidirectionalIter first, BidirectionalIter last, std::tuple<Fn1, Integral1, Fn2, Integral2> xs, Compare comp) const
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, BidirectionalIter>::type,
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, BidirectionalIter>::type,
            is_invocable<Fn1, BidirectionalIter, BidirectionalIter, Compare>,
            is_invocable<Fn2, BidirectionalIter, BidirectionalIter, Compare>,
            is_nothrow_incrementable<BidirectionalIter>,
            is_nothrow_dereferenceable<BidirectionalIter>
        >::value
    )
    {
        do_qsort(first, last, srook::move(xs), comp, SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::iterator_category());
        std::get<2>(xs)(first, last, comp);
    }
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::BidirectionalIterator BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
    template <class BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2>
#endif
    SROOK_FORCE_INLINE void 
    operator()(BidirectionalIter first, BidirectionalIter last, std::tuple<Fn1, Integral1, Fn2, Integral2> xs) const
    SROOK_NOEXCEPT(operator()(first, last, srook::move(xs), srook::functional::deduction_less()))
    {
        operator()(first, last, srook::move(xs), srook::functional::deduction_less());
    }
private:
    template <class BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2, class Compare>
    void do_qsort(BidirectionalIter first, BidirectionalIter last, std::tuple<Fn1, Integral1, Fn2, Integral2> xs, Compare comp, std::bidirectional_iterator_tag tag) const
    {
        if (last - first <= std::get<3>(xs)) return;
        if (!std::get<1>(xs)) {
            std::get<0>(xs)(first, last, comp);
            return;
        }

        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::difference_type diff_type;
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<BidirectionalIter>::value_type value_type;
        const diff_type diff = std::distance(first, last);
            
        if (diff <= 1) return;
        const value_type pivot = *std::next(first, diff / 2);
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        const BidirectionalIter middle1 = std::partition(first, last, std::bind(comp, std::placeholders::_1, pivot));
        const BidirectionalIter middle2 = std::partition(middle1, last, std::bind(srook::functional::not_fn(comp), pivot, std::placeholders::_1));
#else
        const BidirectionalIter middle1 = std::partition(first, last, std::bind2nd(comp, pivot));
        const BidirectionalIter middle2 = std::partition(middle1, last, std::bind1st(srook::functional::not_fn(comp), pivot));
#endif
        do_qsort(first, middle1, std::make_tuple(std::get<0>(xs), std::get<1>(xs) - 1, std::get<2>(xs), std::get<3>(xs)), comp, tag);
        do_qsort(middle2, last, std::make_tuple(std::get<0>(xs), std::get<1>(xs) - 1, std::get<2>(xs), std::get<3>(xs)), comp, tag);
    }

    template <class RandomAccessIter, class Fn1, class Fn2, typename Integral1, typename Integral2,  class Compare>
    void do_qsort(RandomAccessIter first, RandomAccessIter last, std::tuple<Fn1, Integral1, Fn2, Integral2> xs, Compare comp, std::random_access_iterator_tag tag) const
    {
        if (last - first <= std::get<3>(xs)) return;
        if (!std::get<1>(xs)) {
            std::get<0>(xs)(first, last, comp);
            return ;
        }

        if (last - first <= 1) return; 
        RandomAccessIter pi = first + ((last - first) >> 1);
        std::nth_element(first, pi, last, comp);
        do_qsort(first, pi, std::make_tuple(std::get<0>(xs), std::get<1>(xs) - 1, std::get<2>(xs), std::get<3>(xs)), comp, tag); 
        do_qsort(pi, last, std::make_tuple(std::get<0>(xs), std::get<1>(xs) - 1, std::get<2>(xs), std::get<3>(xs)), comp, tag); 
    }
};
    

#if SROOK_HAS_CONCEPTS
template <srook::concepts::BidirectionalIterator BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2, class Compare>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2, class Compare, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
template <class BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2, class Compare>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_invocable, Compare, BidirectionalIter, BidirectionalIter>::type,
        is_invocable<Fn1, BidirectionalIter, BidirectionalIter, Compare>,
        is_invocable<Fn2, BidirectionalIter, BidirectionalIter, Compare>,
        is_integral<Integral1>,
        is_integral<Integral2>
    >::value
>::type
#else
void
#endif
quick_x_sort(BidirectionalIter first, BidirectionalIter last, std::tuple<Fn1, Integral1, Fn2, Integral2> xs, Compare comp)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, BidirectionalIter>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, BidirectionalIter>::type,
        is_nothrow_incrementable<BidirectionalIter>,
        is_nothrow_dereferenceable<BidirectionalIter>,
        is_nothrow_invocable<Fn1, BidirectionalIter, BidirectionalIter, Compare>,
        is_nothrow_invocable<Fn2, BidirectionalIter, BidirectionalIter, Compare>
    >::value
)
{
    srook::algorithm::quick_x_sorting()(first, last, srook::move(xs), comp);
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::BidirectionalIterator BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2, SROOK_REQUIRES(is_bidirectionaliterator<BidirectionalIter>::value)>
#else
template <class BidirectionalIter, class Fn1, class Fn2, typename Integral1, typename Integral2>
#endif
SROOK_FORCE_INLINE void quick_x_sort(BidirectionalIter first, BidirectionalIter last, std::tuple<Fn1, Integral1, Fn2, Integral2> xs)
SROOK_NOEXCEPT(srook::algorithm::quick_x_sort(first, last, srook::move(xs), srook::functional::deduction_less()))
{
    srook::algorithm::quick_x_sort(first, last, srook::move(xs), srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
