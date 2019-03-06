// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_ALGORITHM_TRANSFORM_HPP
#define INCLUDED_ALGORITHM_TRANSFORM_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cxx20/concepts/iterator/InputIterator.hpp>
#include <srook/cxx20/concepts/iterator/OutputIterator.hpp>
#include <srook/type_traits/iterator/is_inputiterator.hpp>
#include <srook/type_traits/iterator/is_outputiterator.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/disable_if.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/is_assignable.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/tuple/algorithm/map.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter, srook::concepts::OutputIterator OutputIter, class UnaryOperation>
#else
template <class InputIter, class OutputIter, class UnaryOperation>
#endif
SROOK_CONSTEXPR auto
transform(InputIter first1, InputIter last1, OutputIter d_first, UnaryOperation unary_op)
-> SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        is_assignable<SROOK_DECLTYPE(*d_first), SROOK_DEDUCED_TYPENAME invoke_result<UnaryOperation, SROOK_DECLTYPE(*first1)>::type>,
        is_inputiterator<InputIter>,
        is_outputiterator<OutputIter>
    >::value,
    OutputIter
>::type
{
    return first1 == last1 ? d_first : (*d_first = unary_op(*first1), ::srook::algorithm::transform(++first1, last1, ++d_first, unary_op));
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter1, srook::concepts::InputIterator InputIter2, srook::concepts::OutputIterator OutputIter, class BinaryOperation>
#else
template <class InputIter1, class InputIter2, class OutputIter, class BinaryOperation>
#endif
SROOK_CONSTEXPR auto
transform(InputIter1 first1, InputIter1 last1, InputIter2 first2, OutputIter d_first, BinaryOperation binary_op)
-> SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        is_assignable<SROOK_DECLTYPE(*d_first), SROOK_DEDUCED_TYPENAME invoke_result<BinaryOperation, SROOK_DECLTYPE(*first1), SROOK_DECLTYPE(*first2)>::type>,
        is_inputiterator<InputIter1>,
        is_inputiterator<InputIter2>,
        is_outputiterator<OutputIter>
    >::value,
    OutputIter
>::type
{
    return first1 == last1 ? d_first : (*d_first = binary_op(*first1, *first2), ::srook::algorithm::transform(++first1, last1, ++first2, d_first, binary_op));
}

#if SROOK_HAS_CONCEPTS
template <class SinglePassRange, srook::concepts::OutputIterator OutputIter, class UnaryOperation>
#else
template <class SinglePassRange, class OutputIter, class UnaryOperation>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR OutputIter
transform(const SinglePassRange& range, OutputIter oiter, UnaryOperation unary_op)
{
    return ::srook::algorithm::transform(range.cbegin(), range.cend(), oiter, unary_op);
}

#if SROOK_HAS_CONCEPTS
template <class SinglePassRange, srook::concepts::InputIterator InputIter2, srook::concepts::OutputIterator OutputIter, class BinaryOperation>
#else
template <class SinglePassRange, class InputIter2, class OutputIter, class BinaryOperation>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME disable_if<is_iterator<SinglePassRange>::value, OutputIter>::type
transform(const SinglePassRange& range, InputIter2 first2, OutputIter oiter, BinaryOperation binary_op)
{
    return ::srook::algorithm::transform(range.cbegin(), range.cend(), first2, oiter, binary_op);
}

template <class... Ts, class UnaryOperation>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<tmpl::vt::bind<invoke_result, UnaryOperation>, Ts...>::type>::type
transform(const std::tuple<Ts...>& ts, UnaryOperation unary_op)
{
    return srook::tuple::map(unary_op, ts);
}
#else

template <class InputIter, class OutputIter, class UnaryOperation>
OutputIter transform(InputIter first1, InputIter last1, OutputIter d_first, UnaryOperation unary_op)
{
    while (first1 != last1) *d_first++ = unary_op(*first1++);
    return d_first;
}

template <class InputIter1, class InputIter2, class OutputIter, class BinaryOperation>
OutputIter transform(InputIter1 first1, InputIter1 last, InputIter2 first2, OutputIter d_first, BinaryOperation binary_op)
{
    while (first1 != last1) *d_first++ = binary_op(*first1++, *first2++);
    return d_first;
}

#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook) // namespace srook

#endif
