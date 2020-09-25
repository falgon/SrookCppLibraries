// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_MIN_ITER_HPP
#define INCLUDED_SROOK_ALGORITHM_MIN_ITER_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/iterator/range_access.hpp>
#include <algorithm>
#include <initializer_list>
#include <iterator>
#ifdef __GNUC__
#   include <bits/stl_function.h>
#else
#   include <functional>
#endif

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <srook::concepts::Iterator Iter, class Compare>
#else
template <class Iter, class Compare>
#endif
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<
        is_iterator<Iter>, 
        is_invocable<Compare, SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type>
    >::value, 
    Iter
>::type
min_iter(Iter x, Iter y, Compare comp)
{
    return comp(*x, *y) ? x : y;
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::Iterator Iter>
#else
template <class Iter>
#endif
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR Iter min_iter(Iter x, Iter y)
{
    return min_iter(x, y, std::less<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type>());
}

template <class T, class Compare>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<is_invocable<Compare, T>::value, SROOK_DEDUCED_TYPENAME std::initializer_list<T>::iterator>::type
min_iter(std::initializer_list<T> t, Compare comp)
{
    return std::min_element(srook::begin(t), srook::end(t), comp);
}

template <class T>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME std::initializer_list<T>::iterator
min_iter(std::initializer_list<T> t)
{
    return min_iter(t, std::less<T>());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)
#endif
