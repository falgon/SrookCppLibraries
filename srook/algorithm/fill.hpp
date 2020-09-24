// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_FILL_HPP
#define INCLUDED_SROOK_ALGORITHM_FILL_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_assignable.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter, class T>
#else
template <class ForwardIter, class T>
#endif
SROOK_CXX14_CONSTEXPR SROOK_FORCE_INLINE void
fill(ForwardIter first, ForwardIter last, const T& value)
{
    for (; first != last; ++first) *first = value;
}

template <class SinglePassRange, class T>
SROOK_CXX14_CONSTEXPR SROOK_FORCE_INLINE void fill(SinglePassRange& range, const T& value)
{
    srook::algorithm::fill(srook::begin(range), srook::end(range), value);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
