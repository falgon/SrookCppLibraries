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
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/is_assignable.hpp>
#include <srook/iterator/range_access.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter, srook::concepts::OutputIterator OutputIter, class UnaryOperation>
#else
template <class InputIter, class OutputIter, class UnaryOperation>
#endif
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_CONSTEXPR auto
#else
SROOK_FORCE_INLINE OutputIter 
#endif
transform(InputIter first1, InputIter last1, OutputIter d_first, UnaryOperation unary_op)
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
-> SROOK_DEDUCED_TYPENAME enable_if<is_assignable<SROOK_DECLTYPE(*d_first), SROOK_DEDUCED_TYPENAME invoke_result<UnaryOperation, SROOK_DECLTYPE(*first1)>::type>::value, OutputIter>::type
#endif
{
    return first1 == last1 ? d_first : (*d_first = unary_op(*first1), transform(++first1, last1, ++d_first, unary_op));
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter1, srook::concepts::InputIterator InputIter2, srook::concepts::OutputIterator OutputIter, class BinaryOperation>
#else
template <class InputIter1, class InputIter2, class OutputIter, class BinaryOperation>
#endif
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_CONSTEXPR auto
#else
SROOK_FORCE_INLINE OutputIter
#endif
transform(InputIter1 first1, InputIter1 last1, InputIter2 first2, OutputIter d_first, BinaryOperation binary_op)
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
-> SROOK_DEDUCED_TYPENAME enable_if<
    is_assignable<SROOK_DECLTYPE(*d_first), SROOK_DEDUCED_TYPENAME invoke_result<BinaryOperation, SROOK_DECLTYPE(*first1), SROOK_DECLTYPE(*first2)>::value>::type,
    OutputIter
>::type
#endif
{
    return first1 == last1 ? d_first : (*d_first = binary_op(*first1, *first2), transform(++first1, last1, ++first2, d_first, binary_op));
}

#if SROOK_HAS_CONCEPTS
template <class SinglePassRange, srook::concepts::OutputIterator OutputIter, class UnaryOperation>
#else
template <class SinglePassRange, class OutputIter, class UnaryOperation>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR OutputIter
transform(const SinglePassRange& range, OutputIter oiter, UnaryOperation unary_op)
{
    return ::srook::algorithm::transform(srook::begin(range), srook::end(range), oiter, unary_op);
}

#if SROOK_HAS_CONCEPTS
template <class SinglePassRange, srook::concepts::InputIterator InputIter2, srook::concepts::OutputIterator OutputIter, class BinaryOperation>
#else
template <class SinglePassRange, class InputIter2, class OutputIter, class BinaryOperation>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR OutputIter
transform(const SinglePassRange& range, InputIter2 first2, OutputIter oiter, BinaryOperation binary_op)
{
    return ::srook::algorithm::transform(srook::begin(range), srook::end(range), first2, oiter, binary_op);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook) // namespace srook

#endif
