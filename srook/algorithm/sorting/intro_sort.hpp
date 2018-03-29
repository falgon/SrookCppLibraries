// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_INTRO_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_INTRO_SORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/execution.hpp>
#if SROOK_HAS_THREADS
#   include <srook/thread.hpp>
#   include <vector>
#endif
#include <srook/algorithm/sorting/detail/qsort_helper.hpp>
#include <srook/algorithm/sorting/heap_sort.hpp>
#include <srook/algorithm/sorting/insertion_sort.hpp>
#include <srook/algorithm/med.hpp>
#include <srook/algorithm/for_each.hpp>
#include <srook/math/constants/algorithm/log2.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

class intro_sorting : protected srook::algorithm::detail::qsort_helper {
public:
    typedef std::size_t size_type;

    SROOK_FORCE_INLINE SROOK_CONSTEXPR intro_sorting(size_type depth_limit = 0, size_type threshold = 32)
        : depth_limit_(srook::move(depth_limit)), threshold_(srook::move(threshold)) {}
   
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::RandomAccessIterator RandomAccessIter, class Compare>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class RandomAccessIter, class Compare, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
    template <class RandomAccessIter, class Compare>
#endif
    SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_DEDUCED_TYPENAME enable_if<
        detail::iter_ref_apply<is_invocable, Compare, RandomAccessIter, RandomAccessIter>::type::value
    >::type
#else
    void
#endif
    operator()(RandomAccessIter first, RandomAccessIter last, Compare comp) const
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, RandomAccessIter>::type,
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, RandomAccessIter, RandomAccessIter>::type,
            is_nothrow_incrementable<RandomAccessIter>, is_nothrow_decrementable<RandomAccessIter>,
            is_nothrow_dereferenceable<RandomAccessIter>
        >::value
    )
    {
#ifdef __GNU_LIBRARY__
        __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
        if (SROOK_UNLIKELY(first == last || srook::iterator::next(first) == last)) return;
        do_introsort(first, last, depth_limit_ ? depth_limit_ : static_cast<size_type>(srook::math::log2(last - first)) << 1, comp);
        intro_insertion_sort(first, last, comp);
    }

#if SROOK_HAS_CONCEPTS
    template <srook::concepts::RandomAccessIterator RandomAccessIter>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class RandomAccessIter, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
    template <class RandomAccessIter>
#endif
    SROOK_FORCE_INLINE void operator()(RandomAccessIter first, RandomAccessIter last) const
    SROOK_NOEXCEPT(operator()(first, last, srook::functional::deduction_less()))
    {
#ifdef __GNU_LIBRARY__
        __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
        return operator()(first, last, srook::functional::deduction_less());
    }

#if SROOK_HAS_THREADS
private:
    template <class OutputIter, class RandomAccessIter, class Compare>
    void take_pivots(OutputIter pivots, size_type depth, RandomAccessIter first, RandomAccessIter last, Compare comp) const
    {
        if (!depth) return;
        --depth;
        RandomAccessIter p = partition_pivot(first, last, comp);
        *pivots++ = p;
        take_pivots(pivots, depth, first, p, comp);
        take_pivots(pivots, depth, p, last, comp);
    }
public:
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::RandomAccessIterator RandomAccessIter, class Compare>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class RandomAccessIter, class Compare, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
    template <class RandomAccessIter, class Compare>
#endif
    SROOK_FORCE_INLINE void operator()(srook::execution::sequenced_policy, RandomAccessIter first, RandomAccessIter last, Compare comp) const
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, RandomAccessIter>::type,
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, RandomAccessIter>::type,
            is_nothrow_incrementable<RandomAccessIter>, is_nothrow_decrementable<RandomAccessIter>,
            is_nothrow_dereferenceable<RandomAccessIter>
        >::value
    )
    {
#ifdef __GNU_LIBRARY__
        __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
        operator()(first, last, srook::move(comp));
    }

#if SROOK_HAS_CONCEPTS
    template <srook::concepts::RandomAccessIterator RandomAccessIter, class Compare>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class RandomAccessIter, class Compare, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
    template <class RandomAccessIter, class Compare>
#endif
    SROOK_FORCE_INLINE void operator()(srook::execution::parallel_unsequenced_policy, RandomAccessIter first, RandomAccessIter last, Compare comp) const
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, RandomAccessIter>::type,
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, RandomAccessIter>::type,
            is_nothrow_incrementable<RandomAccessIter>, is_nothrow_decrementable<RandomAccessIter>,
            is_nothrow_dereferenceable<RandomAccessIter>
        >::value
    )
    {
#ifdef __GNU_LIBRARY__
        __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
        operator()(srook::execution::par, first, last, srook::move(comp)); // TODO
    }

#if SROOK_HAS_CONCEPTS
    template <srook::concepts::RandomAccessIterator RandomAccessIter, class Compare>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class RandomAccessIter, class Compare, SROOK_REQUIRES(is_forwarditerator<RandomAccessIter>::value)>
#else
    template <class RandomAccessIter, class Compare>
#endif
    SROOK_FORCE_INLINE void operator()(srook::execution::parallel_policy, RandomAccessIter first, RandomAccessIter last, Compare comp) const
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, RandomAccessIter>::type,
            SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, RandomAccessIter>::type,
            is_nothrow_incrementable<RandomAccessIter>, is_nothrow_decrementable<RandomAccessIter>,
            is_nothrow_dereferenceable<RandomAccessIter>
        >::value
    )
    {
#ifdef __GNU_LIBRARY__
        __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIter>)
#endif
        if (SROOK_UNLIKELY(first == last || srook::iterator::next(first) == last)) return;
        
        const size_type hardware_concurrency = srook::thread::hardware_concurrency();
        std::vector<RandomAccessIter> pivots;

        pivots.reserve(hardware_concurrency);
        take_pivots(std::back_inserter(pivots), hardware_concurrency >> 1, first, last, comp);
        // In order to simpligy indexing, linearizing the vectors that are recursively structured.
        // Since the size of elements is usually small, it should not cost most of the load.
        srook::algorithm::insertion_sort(srook::begin(pivots), srook::end(pivots)); 

#if !SROOK_CPP_LAMBDAS
        const auto invoke_introsort = 
            [] (const intro_sorting* const this_, RandomAccessIter b, RandomAccessIter e, size_type limit, Compare comp) 
            SROOK_NOEXCEPT(this_->do_introsort(b, e, limit, comp))
            { 
                this_->do_introsort(b, e, limit, comp); 
            };
        const auto joiner = [] (auto&& th) { th.join(); };
#else
        const struct ieit {
            SROOK_FORCE_INLINE void operator()(const intro_sorting* const this_, RandomAccessIter b, RandomAccessIter e, size_type limit, Compare comp) const
            SROOK_NOEXCEPT(this_->do_introsort(b, e, limit, comp))
            {
                this_->do_introsort(b, e, limit, comp);
            }
        } invoke_introsort = {};
        const struct jr {
            SROOK_FORCE_INLINE void operator()(srook::thread& th) const { th.join(); }
        } joiner = {};
#endif

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#   define SROOK_INTRO_SORT_EMPLACE_BACK(...) emplace_back(__VA_ARGS__)
#else
#   define SROOK_INTRO_SORT_EMPLACE_BACK(...) push_back(srook::thread(__VA_ARGS__))
#endif
        std::vector<srook::thread> threads;
        const size_type depth_limit = depth_limit_ ? depth_limit_ : static_cast<size_type>(std::log2(last - first)) << 1;
        
        threads.SROOK_INTRO_SORT_EMPLACE_BACK(invoke_introsort, this, first, *srook::begin(pivots), depth_limit, comp);
        for (SROOK_DEDUCED_TYPENAME std::vector<RandomAccessIter>::iterator iter = srook::begin(pivots); iter + 1 < srook::end(pivots); ++iter) {
            threads.SROOK_INTRO_SORT_EMPLACE_BACK(invoke_introsort, this, *iter, *srook::iterator::next(iter), depth_limit, comp);
        }
        threads.SROOK_INTRO_SORT_EMPLACE_BACK(invoke_introsort, this, *srook::iterator::prev(srook::end(pivots)), last, depth_limit, comp);
        srook::for_each(threads, srook::move(joiner));
        intro_insertion_sort(first, last, comp);
#undef SROOK_INTRO_SORT_EMPLACE_BACK
    }
#endif

private:
    template <class RandomAccessIter, class Compare>
    SROOK_FORCE_INLINE void intro_insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp) const
    {
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<RandomAccessIter>::value_type value_type;
        for (RandomAccessIter iter = srook::iterator::next(first); iter != last; ++iter) {
            RandomAccessIter iter2 = iter;
            value_type t(srook::move(*iter));
            for (RandomAccessIter k = iter; k != first && comp(t, *--k); --iter2) *iter2 = srook::move(*k);
            *iter2 = srook::move(t);
        }
    }

    template <class RandomAccessIter, class Compare>
    void do_introsort(RandomAccessIter first, RandomAccessIter last, size_type depth_limit, Compare comp) const
    {
        while (static_cast<size_type>(last - first) > threshold_) {
            if (!depth_limit) {
                srook::algorithm::heap_sort(first, last, comp);
                return;
            }
            --depth_limit;
            RandomAccessIter partial = partition_pivot(first, last, comp);
            do_introsort(partial, last, depth_limit, comp);
            last = partial;
        }
    }

    template <class RandomAccessIter, class Compare>
    SROOK_FORCE_INLINE RandomAccessIter partition(RandomAccessIter first, RandomAccessIter last, RandomAccessIter pivot, Compare comp) const
    {
        while (true) {
            while (comp(*first, *pivot)) ++first;
            --last;
            while (comp(*pivot, *last)) --last;
            if (!(first < last)) return first;
            std::iter_swap(first, last);
            ++first;
        }
        return first;
    }

    template <class RandomAccessIter, class Compare>
    SROOK_FORCE_INLINE RandomAccessIter partition_pivot(RandomAccessIter first, RandomAccessIter last, Compare comp) const
    {
        move_median_to_first(first, first + 1, first + ((last - first) >> 1), last - 1, comp);
        return partition(first + 1, last, first, comp);
    }

    const size_type depth_limit_, threshold_;
};

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
intro_sort(ExecutionPolicy&& exp, RandomAccessIter first, RandomAccessIter last, Compare comp)
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
intro_sort(ExecutionPolicy&& exp, RandomAccessIter first, RandomAccessIter last)
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
SROOK_DEDUCED_TYPENAME 
enable_if<detail::iter_ref_apply<is_invocable, Compare, RandomAccessIter, RandomAccessIter>::type::value>::type
#else
void
#endif
intro_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
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
SROOK_FORCE_INLINE void intro_sort(RandomAccessIter first, RandomAccessIter last)
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
