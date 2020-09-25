// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_ALGORITHM_LEAST_SQUARE_HPP
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_ALGORITHM_LEAST_SQUARE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/math/linear_algebra/vector/impl.h>
#include <srook/tmpl/vt/replicate.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tuple/algorithm/foldr1.hpp>
#include <srook/tuple/algorithm/zip_with.hpp>
#include <srook/execution.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)

template <class E1, class... Elems1, class E2, class... Elems2>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<
    sizeof...(Elems1) == sizeof...(Elems2), 
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::pair, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<2, SROOK_DEDUCED_TYPENAME std::common_type<E1, Elems1..., E2, Elems2...>::type>::type>::type
>::type
least_squares(const detail::vector_impl<E1, Elems1...>& xs, const detail::vector_impl<E2, Elems2...>& ys)
{
    SROOK_CONSTEXPR std::size_t len = sizeof...(Elems1) + 1;
    const auto res = tuple::foldr1(
        [](const auto& d, const auto& acc) { return tuple::zip_with(std::plus<>{}, d, acc); },
        tuple::zip_with([](const auto& x, const auto& y) { return std::make_tuple(x * y, x, y, x * x); }, xs.to_tuple(), ys.to_tuple())
    );
    return 
        std::make_pair(
            (len * std::get<0>(res) - std::get<1>(res) * std::get<2>(res)) / (len * std::get<3>(res) - std::get<1>(res) * std::get<1>(res)), 
            (std::get<3>(res) * std::get<2>(res) - std::get<0>(res) * std::get<1>(res)) / (len * std::get<3>(res) - std::get<1>(res) * std::get<1>(res))
        );
}

template <class E1, class... Elems1, class E2, class... Elems2>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<
    sizeof...(Elems1) == sizeof...(Elems2),
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::pair, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<2, SROOK_DEDUCED_TYPENAME std::common_type<E1, Elems1..., E2, Elems2...>::type>::type>::type
>::type
least_squares(srook::execution::sequenced_policy, const detail::vector_impl<E1, Elems1...>& xs, const detail::vector_impl<E2, Elems2...>& ys)
{
    return least_squares(xs, ys);
}

template <class E1, class... Elems1, class E2, class... Elems2>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
enable_if<
    sizeof...(Elems1) == sizeof...(Elems2),
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::pair, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<2, SROOK_DEDUCED_TYPENAME std::common_type<E1, Elems1..., E2, Elems2...>::type>::type>::type
>::type
least_squares(srook::execution::parallel_policy par, const detail::vector_impl<E1, Elems1...>& xs, const detail::vector_impl<E2, Elems2...>& ys)
{
    SROOK_CONSTEXPR std::size_t len = sizeof...(Elems1) + 1;
    const auto res = tuple::foldr1(
        [&par](const auto& d, const auto& acc) { return tuple::zip_with(par, std::plus<>{}, d, acc); },
        tuple::zip_with(par, [](const auto& x, const auto& y) { return std::make_tuple(x * y, x, y, x * x); }, xs.to_tuple(), ys.to_tuple())
    );
    return 
        std::make_pair(
            (len * std::get<0>(res) - std::get<1>(res) * std::get<2>(res)) / (len * std::get<3>(res) - std::get<1>(res) * std::get<1>(res)), 
            (std::get<3>(res) * std::get<2>(res) - std::get<0>(res) * std::get<1>(res)) / (len * std::get<3>(res) - std::get<1>(res) * std::get<1>(res))
        );
}

template <class E1, class... Elems1, class E2, class... Elems2>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
enable_if<
    sizeof...(Elems1) == sizeof...(Elems2),
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::pair, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<2, SROOK_DEDUCED_TYPENAME std::common_type<E1, Elems1..., E2, Elems2...>::type>::type>::type
>::type
least_squares(srook::execution::parallel_unsequenced_policy, const detail::vector_impl<E1, Elems1...>& xs, const detail::vector_impl<E2, Elems2...>& ys)
{
    return least_squares(srook::execution::par, xs, ys);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
