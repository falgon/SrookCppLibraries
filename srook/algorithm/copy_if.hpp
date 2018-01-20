// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_COPY_IF_HPP
#define INCLUDED_SROOK_ALGORITHM_COPY_IF_HPP

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
template <srook::concepts::InputIterator InputIter, srook::concepts::OutputIterator OutputIter, class UnaryPredicate>
#else
template <class InputIter, class OutputIter, class UnaryPredicate>
#endif
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_invocable<UnaryPredicate, SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type>::value, OutputIter>::type
copy_if(InputIter first, InputIter last, OutputIter d_first, UnaryPredicate pred)
{
    return first == last ? d_first : pred(*first) ? (*d_first = *first, copy_if(++first, last, ++d_first, pred)) : srook::algorithm::copy_if(++first, last, d_first, pred);
}

#if SROOK_HAS_CONCEPTS
template <class SinglePassRange, srook::concepts::OutputIterator OutputIter, class UnaryPredicate>
#else
template <class SinglePassRange, class OutputIter, class UnaryPredicate>
#endif
SROOK_CONSTEXPR OutputIter copy_if(const SinglePassRange& range, OutputIter d_first, UnaryPredicate pred)
{
    return srook::algorithm::copy_if(srook::begin(range), srook::end(range), d_first, pred);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
