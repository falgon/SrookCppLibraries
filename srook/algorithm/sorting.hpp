// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SORTING_HPP
#define INCLUDED_SROOK_ALGORITHM_SORTING_HPP

#include <srook/algorithm/sorting/bubble_sort.hpp>
#include <srook/algorithm/sorting/bucket_sort.hpp>
#include <srook/algorithm/sorting/comb_sort.hpp>
#include <srook/algorithm/sorting/counting_sort.hpp>
#include <srook/algorithm/sorting/gnome_sort.hpp>
#include <srook/algorithm/sorting/heap_sort.hpp>
#include <srook/algorithm/sorting/insertion_sort.hpp>
#include <srook/algorithm/sorting/intro_sort.hpp>
#include <srook/algorithm/sorting/merge_sort.hpp>
#include <srook/algorithm/sorting/odd_even_sort.hpp>
#include <srook/algorithm/sorting/quick_sort.hpp>
#include <srook/algorithm/sorting/quick_x_sort.hpp>
#include <srook/algorithm/sorting/selection_sort.hpp>
#include <srook/algorithm/sorting/shaker_sort.hpp>
#include <srook/algorithm/sorting/shell_sort.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_THREADS
#if SROOK_HAS_CONCEPTS
template <srook::concepts::RandomAccessIterator RandomAccessIter, class ExecutionPolicy, class Compare>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class RandomAccessIter, class ExecutionPolicy, class Compare, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
template <class RandomAccessIter, class ExecutionPolicy, class Compare>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_invocable, Compare, RandomAccessIter, RandomAccessIter>::type,
        srook::execution::is_execution_policy<SROOK_DEDUCED_TYPENAME decay<ExecutionPolicy>::type>
    >::value
>::type
#else
void
#endif
sort(ExecutionPolicy&& exp, RandomAccessIter first, RandomAccessIter last, Compare comp)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, RandomAccessIter>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, RandomAccessIter>::type,
        is_nothrow_incrementable<RandomAccessIter>,
        is_nothrow_dereferenceable<RandomAccessIter>
    >::value
)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
    srook::algorithm::intro_sorting()(srook::forward<ExecutionPolicy>(exp), first, last, srook::move(comp));
}


#if SROOK_HAS_CONCEPTS
template <srook::concepts::RandomAccessIterator RandomAccessIter, class ExecutionPolicy>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class RandomAccessIter, class ExecutionPolicy, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
template <class RandomAccessIter, class ExecutionPolicy>
#endif
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<srook::execution::is_execution_policy<SROOK_DEDUCED_TYPENAME decay<ExecutionPolicy>::type>::value>::type
#else
void
#endif
sort(ExecutionPolicy&& exp, RandomAccessIter first, RandomAccessIter last)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, RandomAccessIter>::type,
        is_nothrow_incrementable<RandomAccessIter>,
        is_nothrow_dereferenceable<RandomAccessIter>
    >::value
)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
    srook::algorithm::intro_sorting()(srook::forward<ExecutionPolicy>(exp), first, last, srook::functional::deduction_less());
}
#endif


#if SROOK_HAS_CONCEPTS
template <srook::concepts::RandomAccessIterator RandomAccessIter, class Compare>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class RandomAccessIter, class Compare, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
template <class RandomAccessIter, class Compare>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME enable_if<detail::iter_ref_apply<is_invocable, Compare, RandomAccessIter, RandomAccessIter>::type::value>::type
#else
void
#endif
sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, RandomAccessIter>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, RandomAccessIter>::type,
        is_nothrow_incrementable<RandomAccessIter>,
        is_nothrow_dereferenceable<RandomAccessIter>
    >::value
)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
    srook::algorithm::intro_sorting()(first, last, srook::move(comp));
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::RandomAccessIterator RandomAccessIter>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class RandomAccessIter, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
template <class RandomAccessIter>
#endif
SROOK_FORCE_INLINE void sort(RandomAccessIter first, RandomAccessIter last)
SROOK_NOEXCEPT(srook::algorithm::intro_sort(first, last, srook::functional::deduction_less()))
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
    srook::algorithm::intro_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
