// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_MIN_HPP
#define INCLUDED_SROOK_ALGORITHM_MIN_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <initializer_list>
#include <algorithm>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
SROOK_FORCE_INLINE SROOK_CONSTEXPR const T& min(const T& a, const T& b)
{
    return a < b ? a : b;
}

template <class T, class Compare>
SROOK_FORCE_INLINE SROOK_CONSTEXPR const SROOK_DEDUCED_TYPENAME enable_if<is_invocable<Compare, T, T>::value, const T&>::type
min(const T& a, const T& b, Compare comp)
{
    return comp(a, b) ? a : b;
}

template <class T>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR T min(std::initializer_list<T> t)
{
    return *std::min_element(t.begin(), t.end());
}

template <class T, class Compare>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_invocable<Compare, T>::value, T>::type 
min(std::initializer_list<T> t, Compare comp)
{
    return *std::min_element(t.begin(), t.end(), comp);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
