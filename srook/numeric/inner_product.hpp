// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_INNER_PRODUCT_HPP
#define INCLUDED_SROOK_NUMERIC_INNER_PRODUCT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/numeric/detail/config.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
#include <srook/type_traits/is_copy_assignable.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <numeric>

SROOK_NESTED_NAMESPACE(srook, numeric) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool>
struct inner_producter {
    template <SROOK_ARITHMETIC_ITER Iter1, SROOK_ARITHMETIC_ITER Iter2, typename T>
    static SROOK_FORCE_INLINE T do_inner_product(Iter1 first1, Iter1 last1, Iter2 first2, T value)
    {
        return std::inner_product(first1, last1, first2, value);
    }
    template <SROOK_ARITHMETIC_ITER Iter1, SROOK_ARITHMETIC_ITER Iter2, typename T, class BinaryOp1, class BinaryOp2>
    static SROOK_FORCE_INLINE T do_inner_product(Iter1 first1, Iter1 last1, Iter2 first2, T value, BinaryOp1 op1, BinaryOp2 op2)
    {
        return std::inner_product(first1, last1, first2, value, op1, op2);
    }
};

template <>
struct inner_producter<true> {
    template <SROOK_ARITHMETIC_ITER Iter1, SROOK_ARITHMETIC_ITER Iter2, typename T>
    static SROOK_CONSTEXPR T do_inner_product(Iter1 first1, Iter1 last1, Iter2 first2, T value)
    {
        return first1 == last1 ? value : do_inner_product(first1 + 1, last1, first2 + 1, value + *first1 * *first2);
    }
    template <SROOK_ARITHMETIC_ITER Iter1, SROOK_ARITHMETIC_ITER Iter2, typename T, class BinaryOp1, class BinaryOp2>
    static SROOK_CONSTEXPR T do_inner_product(Iter1 first1, Iter1 last1, Iter2 first2, T value, BinaryOp1 op1, BinaryOp2 op2)
    {
        return first1 == last1 ? value : do_inner_product(first1 + 1, last1, first2 + 1, op1(value, op2(*first1, *first2)), op1, op2);
    }
};

} // namespace detail

template <
    SROOK_ARITHMETIC_ITER Iter1, SROOK_ARITHMETIC_ITER Iter2, typename T,
    SROOK_REQUIRES(type_traits::detail::Land<is_copy_constructible<T>, is_copy_assignable<T&>, SROOK_ARITHMETIC_ITER_REQUIRES(Iter)>::value)
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T inner_product(Iter1 first1, Iter1 last1, Iter2 first2, T value)
{
    typedef type_traits::detail::Land<detail::is_arithmetic_addable_iter<Iter1>, detail::is_arithmetic_addable_iter<Iter2>> deduct_type;
    return detail::inner_producter<deduct_type::value>::do_inner_product(first1, last1, first2, value);
}

template <
    SROOK_ARITHMETIC_ITER Iter1, SROOK_ARITHMETIC_ITER Iter2, typename T, class BinaryOp1, class BinaryOp2,
    SROOK_REQUIRES(
        type_traits::detail::Land<
            is_invocable<BinaryOp1, T, SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter1>::value_type>,
            is_invocable<BinaryOp2, T, SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter2>::value_type>,
            is_copy_constructible<T>,
            is_copy_assignable<T>,
            SROOK_ARITHMETIC_ITER_REQUIRES(Iter)
        >::value
    )
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T inner_product(Iter1 first1, Iter1 last1, Iter2 first2, T value, BinaryOp1 op1, BinaryOp2 op2)
{
    typedef type_traits::detail::Land<detail::is_arithmetic_addable_iter<Iter1>, detail::is_arithmetic_addable_iter<Iter2>> deduct_type;
    return detail::inner_producter<deduct_type::value>::do_inner_product(first1, last1, first2, value, op1, op2);
}

template <
    class SinglePassRange, SROOK_ARITHMETIC_ITER Iter, typename T, 
    SROOK_REQUIRES(type_traits::detail::Land<is_copy_constructible<T>, is_copy_assignable<T&>, SROOK_ARITHMETIC_ITER_REQUIRES(Iter)>::value)
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T inner_product(const SinglePassRange& range, Iter first, T value)
{
    return srook::numeric::inner_product(std::begin(range), std::end(range), first, value);
}

template <
    class SinglePassRange, SROOK_ARITHMETIC_ITER Iter, typename T, class BinaryOp1, class BinaryOp2,
    SROOK_REQUIRES(type_traits::detail::Land<is_copy_constructible<T>, is_copy_assignable<T&>, SROOK_ARITHMETIC_ITER_REQUIRES(Iter)>::value)
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T inner_product(const SinglePassRange& range, Iter first, T value, BinaryOp1 op1, BinaryOp2 op2)
{
    return srook::numeric::inner_product(std::begin(range), std::end(range), first, value, op1, op2);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(numeric, srook)

#endif
