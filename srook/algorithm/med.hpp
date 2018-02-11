// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_MED_HPP
#define INCLUDED_SROOK_ALGORITHM_MED_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/algorithm/med_element.hpp>
#include <srook/algorithm/min.hpp>
#include <srook/algorithm/max.hpp>
#include <srook/cxx20/concepts/iterator/RandomAccessIterator.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
SROOK_FORCE_INLINE SROOK_CONSTEXPR const T& med(const T& x, const T& y, const T& z)
{
    return srook::algorithm::max(srook::algorithm::min(x, y), srook::algorithm::min(srook::algorithm::max(x, y), z));
}

template <class T>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR T med(std::initializer_list<T> t)
{
    return *srook::algorithm::med_element(t.begin(), t.end());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)
#endif
