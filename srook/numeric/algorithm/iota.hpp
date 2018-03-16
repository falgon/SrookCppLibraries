// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_ALGORITHM_IOTA_HPP
#define INCLUDED_SROOK_NUMERIC_ALGORITHM_IOTA_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/numeric/algorithm/detail/config.hpp>
#include <srook/type_traits/is_incrementable.hpp>
#include <srook/type_traits/is_range.hpp>
#include <srook/algorithm/for_each.hpp>
#include <srook/iterator/range_access.hpp>
#if SROOK_HAS_THREADS
#   include <srook/thread.hpp>
#endif

SROOK_NESTED_NAMESPACE(srook, numeric, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(Iter first, Iter last, T value)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>, 
        is_nothrow_preincrementable<Iter>, 
        is_nothrow_postincrementable<T&>
    >::value
)
{
#ifdef __GNU_LIBRARY__
    __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<Iter>)
    __glibcxx_function_requires(_ConvertibleConcept<T, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::value_type>)
    __glibcxx_requires_valid_range(first, last);
#endif
    for (; first != last; ++first) *first = value++;
}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class Range, class T, SROOK_REQUIRES(is_range<Range>::value)>
#else
template <class Range, class T>
#endif
SROOK_FORCE_INLINE void iota(Range& range, T val)
SROOK_NOEXCEPT(srook::algorithm::iota(srook::begin(range), srook::end(range), val))
{
    srook::numeric::algorithm::iota(srook::begin(range), srook::end(range), val);
}

#if SROOK_HAS_THREADS
namespace detail {

template <class Iter, class T>
SROOK_FORCE_INLINE void iota_parallel(Iter first, Iter last, T value)
{
    const std::size_t hardware_concurrency = srook::thread::hardware_concurrency();
    if (!hardware_concurrency) {
        srook::numeric::algorithm::iota(first, last, value);
        return;
    }

    const std::size_t one_thread = std::distance(first, last) / hardware_concurrency;
    if (!one_thread) {
        srook::numeric::algorithm::iota(first, last, value);
        return;
    }
    
    std::vector<srook::thread> threads;
    Iter this_thread_last = srook::iterator::next(first, one_thread);
#if SROOK_CPP_LAMBDAS
    const auto ioter = [](Iter b, Iter e, T v) SROOK_NOEXCEPT(srook::numeric::algorithm::iota(b, e, v)) { srook::numeric::algorithm::iota(b, e, v); };
    const auto joiner = [](auto&& th) { th.join(); };
#else
    struct iot {
        SROOK_FORCE_INLINE void operator()(Iter b, Iter e, T v) const
        SROOK_NOEXCEPT(srook::numeric::algorithm::iota(b, e, v)) { srook::numeric::algorithm::iota(b, e, v); }
    } ioter;
    struct joi {
        template <class Thread>
        SROOK_FORCE_INLINE void operator()(Thread&& th) const { th.join(); }
    } joiner;
#endif

    for (std::size_t i = 0u; i < hardware_concurrency; ++i) {
        threads.emplace_back(ioter, first, this_thread_last, value);
        srook::iterator::advance(first, one_thread);
        srook::iterator::advance(this_thread_last, one_thread);
        value += static_cast<T>(one_thread);
    }
    Iter last_prev = srook::prev(this_thread_last);
    if (last_prev < last) srook::numeric::algorithm::iota(last_prev, last, value);
    srook::algorithm::for_each(threads, srook::move(joiner));
}

} // namespace detail


#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(srook::execution::sequenced_policy, Iter first, Iter last, T value)
SROOK_NOEXCEPT(srook::numeric::algorithm::iota(first, last, value))
{
    srook::numeric::algorithm::iota(first, last, value);
}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(srook::execution::parallel_policy, Iter first, Iter last, T value)
{
    srook::numeric::algorithm::detail::iota_parallel(first, last, value);
}


#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(srook::execution::parallel_unsequenced_policy, Iter first, Iter last, T value)
{
    srook::numeric::algorithm::detail::iota_parallel(first, last, value); // TODO
}

#ifdef SROOK_HAS_STD_EXECUTION
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(std::execution::sequenced_policy, Iter first, Iter last, T value)
SROOK_NOEXCEPT(srook::numeric::algorithm::iota(first, last, value))
{
    srook::numeric::algorithm::iota(first, last, value);
}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(std::execution::parallel_policy, Iter first, Iter last, T value)
{
    srook::numeric::algorithm::detail::iota_parallel(first, last, value);
}


#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(std::execution::parallel_unsequenced_policy, Iter first, Iter last, T value)
{
    srook::numeric::algorithm::detail::iota_parallel(first, last, value); // TODO
}

#endif // SROOK_HAS_STD_EXECUTION

#ifdef SROOK_HAS_STD_EXPERIMENTAL_EXECUTION_POLICY
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(std::experimental::parallel::sequential_execution_policy, Iter first, Iter last, T value)
SROOK_NOEXCEPT(srook::numeric::algorithm::iota(first, last, value))
{
    srook::numeric::algorithm::iota(first, last, value);
}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(std::experimental::parallel::parallel_execution_policy, Iter first, Iter last, T value)
{
    srook::numeric::algorithm::detail::iota_parallel(first, last, value);
}
#endif

#if 0 // TODO: Not defined only std::experimental::parallel::parallel_vector_execution_policy ?
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <
    SROOK_ARITHMETIC_ITER Iter, 
    class T, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter), 
            is_assignable<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&, T&>
        >::value    
    )
>
#else
template <class Iter, class T>
#endif
SROOK_FORCE_INLINE void iota(std::experimental::parallel::parallel_vector_execution_policy, Iter first, Iter last, T value)
{
    srook::numeric::algorithm::detail::iota_parallel(first, last, value); // TODO
}
#endif

#endif // SROOK_HAS_STD_EXPERIMENTAL_EXECUTION_POLICY

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class ExecutionPolicy, class Range, class T,
    SROOK_REQUIRES(
        type_traits::detail::Land<
            is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>, 
            execution::is_execution_policy<SROOK_DEDUCED_TYPENAME decay<ExecutionPolicy>::type>,
            is_assignable<SROOK_DEDUCED_TYPENAME decay<Range>::type::value_type&, T&>
        >::value
    )
>
#else
template <class ExecutionPolicy, class Range, class T>
#endif
#if SROOK_CPP_RVALUE_REFERENCES
SROOK_FORCE_INLINE void iota(ExecutionPolicy&& policy, Range&& range, T value)
#else
SROOK_FORCE_INLINE void iota(const ExecutionPolicy& policy, Range& range, T value)
#endif
{
    srook::numeric::algorithm::iota(srook::forward<ExecutionPolicy>(policy), srook::begin(range), srook::end(range), srook::move(value));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, numeric, srook)

#endif
