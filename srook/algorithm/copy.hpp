// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_COPY_HPP
#define INCLUDED_SROOK_ALGORITHM_COPY_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/cxx20/concepts/iterator/InputIterator.hpp>
#include <srook/cxx20/concepts/iterator/OutputIterator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/disable_if.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/iterator/is_inputiterator.hpp>
#include <srook/type_traits/iterator/is_outputiterator.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter, srook::concepts::OutputIterator OutputIter>
#else
template <class InputIter, class OutputIter>
#endif
OutputIter//SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<type_traits::detail::Land<is_inputiterator<InputIter>, is_outputiterator<OutputIter>>::value, OutputIter>::type 
copy(InputIter first, InputIter last, OutputIter d_first)
{
    return first == last ? d_first : (*d_first = *first, srook::algorithm::copy(++first, last, ++d_first));
}

#if SROOK_HAS_CONCEPTS
template <class SinglePassRange, srook::concepts::OutputIterator OutputIter>
#else
template <class SinglePassRange, class OutputIter>
#endif
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME disable_if<is_iterator<SinglePassRange>::value, OutputIter>::type
copy(const SinglePassRange& range, OutputIter d_first)
{
    return srook::algorithm::copy(srook::begin(range), srook::end(range), d_first);
}

#else

template <class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter d_first)
{
    while (first != last) *d_first++ = *first++;
    return d_first;
}

#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
