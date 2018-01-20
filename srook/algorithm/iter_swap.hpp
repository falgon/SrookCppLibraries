// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_ITER_SWAP_HPP
#define INCLUDED_SROOK_ALGORITHM_ITER_SWAP_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/cxx20/concepts/Swappable.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
namespace detail {

template <class T>
SROOK_CONCEPT SwappableAndForwardIter = 
    srook::concepts::Swappable<SROOK_DEDUCED_TYPENAME std::iterator_traits<T>::value_type> &&
    srook::concepts::ForwardIterator<T>;

} // namespace detail

template <srook::algorithm::detail::SwappableAndForwardIter ForwardIter>
#else
template <class ForwardIter>
#endif
SROOK_CXX14_CONSTEXPR void iter_swap(ForwardIter a, ForwardIter b)
{
    using std::swap;
    swap(*a, *b);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)


#endif
