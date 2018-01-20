// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_MAX_HPP
#define INCLUDED_SROOK_ALGORITHM_MAX_HPP

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
SROOK_FORCE_INLINE SROOK_CONSTEXPR const T& max(const T& a, const T& b)
{
    return a < b ? b : a;
}

template <class T, class Compare>
SROOK_FORCE_INLINE SROOK_CONSTEXPR const SROOK_DEDUCED_TYPENAME enable_if<is_invocable<Compare, T, T>::value, T&>::type
max(const T& a, const T& b, Compare comp)
{
    return comp(a, b) ? a : b;
}

template <class T>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR T max(std::initializer_list<T> t)
{
    return *std::max_element(t.begin(), t.end());
}

template <class T, class Compare>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_invocable<Compare, T>::value, T>::type 
max(std::initializer_list<T> t, Compare comp)
{
    return *std::max_element(t.begin(), t.end(), comp);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
