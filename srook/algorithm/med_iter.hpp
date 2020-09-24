// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_MED_ITER_HPP
#define INCLUDED_SROOK_ALGORITHM_MED_ITER_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/algorithm/max_iter.hpp>
#include <srook/algorithm/min_iter.hpp>
#include <srook/algorithm/med_element.hpp>
#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/cxx20/concepts/iterator/RandomAccessIterator.hpp>
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
/*
#if SROOK_HAS_CONCEPTS
template <srook::concepts::RandomAccessIterator Iter>
#else
template <class Iter>
#endif
Iter med_element(Iter, Iter);*/

#if SROOK_HAS_CONCEPTS
template <srook::concepts::Iterator Iter>
#else
template <class Iter>
#endif
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR Iter med_iter(Iter x, Iter y, Iter z)
{
    return srook::algorithm::max_iter(srook::algorithm::min_iter(x, y), srook::algorithm::min_iter(srook::algorithm::max_iter(x, y), z));
}
/*
template <class T>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME std::initializer_list<T>::iterator
med_iter(std::initializer_list<T> t)
{
    return srook::algorithm::med_element(srook::begin(t), srook::end(t));
}
*/
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)
#endif
