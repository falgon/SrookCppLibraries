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
#include <srook/type_traits/is_preincrementable.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/iterator/is_inputiterator.hpp>
#include <srook/type_traits/iterator/is_outputiterator.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/type_traits/is_dereferenceable.hpp>
#include <srook/type_traits/is_range.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPP_CONSTEXPR && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter, srook::concepts::OutputIterator OutputIter>
#else
template <class InputIter, class OutputIter>
#endif
SROOK_CONSTEXPR OutputIter copy(InputIter first, InputIter last, OutputIter d_first)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_preincrementable<InputIter>, 
        is_nothrow_preincrementable<OutputIter>, 
        is_nothrow_dereferenceable<InputIter>, 
        is_nohtorw_dereferenceable<OutputIter>,
        is_nothrow_equality_comparable<InputIter>
    >::value
)
{
    return first != last ? (*d_first = *first, srook::algorithm::copy(++first, last, ++d_first)) : d_first;
}

#else
    
#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter, srook::concepts::OutputIterator OutputIter>
#else
template <class InputIter, class OutputIter>
#endif
SROOK_FORCE_INLINE OutputIter
copy(InputIter first, InputIter last, OutputIter d_first)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_preincrementable<InputIter>, 
        is_nothrow_preincrementable<OutputIter>, 
        is_nothrow_dereferenceable<InputIter>, 
        is_nohtorw_dereferenceable<OutputIter>,
        is_nothrow_equality_comparable<InputIter>
    >::value
)
{
    while (first != last) *d_first++ = *first++;
    return d_first;
}
#endif

#if SROOK_HAS_CONCEPTS
template <class SinglePassRange, srook::concepts::OutputIterator OutputIter>
#else
template <class SinglePassRange, class OutputIter, 
SROOK_REQUIRES(is_range<SROOK_DEDUCED_TYPENAME decay<SinglePassRange>::type>::value)>
#endif
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<is_range<SinglePassRange>::value, OutputIter>::type
copy(const SinglePassRange& range, OutputIter d_first)
SROOK_NOEXCEPT(srook::algorithm::copy(srook::begin(range), srook::end(range), d_first))
{
    return srook::algorithm::copy(srook::begin(range), srook::end(range), d_first);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)
#endif
