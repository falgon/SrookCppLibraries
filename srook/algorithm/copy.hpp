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

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter, srook::concepts::OutputIterator OutputIter>
#else
template <class InputIter, class OutputIter>
#endif
SROOK_CONSTEXPR OutputIter copy(InputIter first, InputIter last, OutputIter d_first)
{
    return first == last ? d_first : (*d_first = *first, srook::algorithm::copy(++first, last, ++d_first));
}

#if SROOK_HAS_CONCEPTS
template <class SinglePassRange, srook::concepts::OutputIterator OutputIter>
#else
template <class SinglePassRange, class OutputIter>
#endif
SROOK_CONSTEXPR OutputIter copy(const SinglePassRange& range, OutputIter d_first)
{
    return srook::algorithm::copy(srook::begin(range), srook::end(range), d_first);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
