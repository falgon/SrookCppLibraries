// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_ACCUMULATE_HPP
#define INCLUDED_SROOK_NUMERIC_ACCUMULATE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/numeric/detail/config.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_copy_assignable.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <numeric>

SROOK_NESTED_NAMESPACE(srook, numeric) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool>
struct accumulator {
    template <SROOK_ARITHMETIC_ITER Iter, typename T>
    static SROOK_FORCE_INLINE T do_accumulate(Iter first, Iter last, T init)
    {
        return std::accumulate(first, last, init);
    }
    template <SROOK_ARITHMETIC_ITER Iter, typename T, class BinaryOp>
    static SROOK_FORCE_INLINE T do_accumulate(Iter first, Iter last, T init, BinaryOp op)
    {
        return std::accumulate(first, last, init, op);
    }
};

template <>
struct accumulator<true> {
    template <SROOK_ARITHMETIC_ITER Iter, typename T>
    static SROOK_CONSTEXPR T do_accumulate(Iter first, Iter last, T init)
    {
        return first == last ? init : do_accumulate(first + 1, last, init + *first);
    }
    template <SROOK_ARITHMETIC_ITER Iter, typename T, class BinaryOp>
    static SROOK_CONSTEXPR T do_accumulate(Iter first, Iter last, T init, BinaryOp op)
    {
        return first == last ? init : do_accumulate(first, 1, last, op(init, *first), op);
    }
};

} // namespace detail

template <
    SROOK_ARITHMETIC_ITER Iter, typename T, 
    SROOK_REQUIRES(type_traits::detail::Land<is_copy_constructible<T>, is_copy_assignable<T&>, SROOK_ARITHMETIC_ITER_REQUIRES(Iter)>::value)
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T accumulate(Iter first, Iter last, T init)
{
    return detail::accumulator<detail::is_arithmetic_addable_iter<Iter>::value>::do_accumulate(first, last, init);
}

template <
    SROOK_ARITHMETIC_ITER Iter, typename T, class BinaryOp, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            is_invocable<BinaryOp, T, SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type>, 
            is_copy_constructible<T>,
            is_copy_assignable<T&>,
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter)
        >::value
    )
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T accumulate(Iter first, Iter last, T init, BinaryOp op)
{
    return detail::accumulator<detail::is_arithmetic_addable_iter<Iter>::value>::do_accumulate(first, last, init, op);
}

template <
    class SinglePassRange, typename T, 
    SROOK_REQUIRES(type_traits::detail::Land<is_copy_constructible<T>, is_copy_assignable<T&>>::value)
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T accumulate(const SinglePassRange& range, T init)
{
    return srook::numeric::accumulate(std::begin(range), std::end(range), init);
}

template <
    class SinglePassRange, typename T, class BinaryOp,
    SROOK_REQUIRES(type_traits::detail::Land<is_copy_constructible<T>, is_copy_assignable<T&>>::value)
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T accumulate(const SinglePassRange& range, T init, BinaryOp op)
{
    return srook::numeric::accumulate(std::begin(range), std::end(range), init, op);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(numeric, srook)

#endif
