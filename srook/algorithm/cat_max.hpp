// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_CAT_MAX_HPP
#define INCLUDED_SROOK_ALGORITHM_CAT_MAX_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/cxx20/concepts/iterator/InputIterator.hpp>
#include <srook/cxx20/concepts/iterator/OutputIterator.hpp>
#include <srook/type_traits/iterator/is_inputiterator.hpp>
#include <srook/type_traits/iterator/is_outputiterator.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/string/to_string.hpp>
#include <srook/algorithm/copy.hpp>
#include <srook/algorithm/transform.hpp>
#include <srook/functional/not_fn.hpp>
#include <algorithm>
#include <functional>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

struct cat_max_default_compare {
    template <class T>
    SROOK_FORCE_INLINE bool operator()(T l, T r)
    {
        const auto ls = srook::string::to_string(l), rs = srook::string::to_string(r);
        return (ls + rs > rs + ls); // To avoid division, arrange them in ascending numerical order
    }
};

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter, class Predicate = detail::cat_max_default_compare>
#else
template <class InputIter, class Predicate = detail::cat_max_default_compare>
#endif
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        is_invocable<Predicate, SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type, SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type>,
        is_inputiterator<InputIter>, 
        is_arithmetic<SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type>
    >::value, 
    SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type
>::type
cat_max(InputIter first, InputIter last, Predicate pred = detail::cat_max_default_compare())
{
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type ivalue_type;
    ivalue_type res = 0;

    std::vector<ivalue_type> t(first, last);
    std::sort(t.begin(), t.end(), srook::functional::not_fn(pred));
    {
        ivalue_type digit = 1;
        for (const auto& v : t) {
            res += v * digit;
            digit *= 10;
        }
    }
    return res;
}

template <class SinglePassRange, class Predicate = detail::cat_max_default_compare>
SROOK_DEDUCED_TYPENAME disable_if<is_iterator<SinglePassRange>::value, SROOK_DEDUCED_TYPENAME SinglePassRange::value_type>::type
cat_max(const SinglePassRange& range, Predicate pred = detail::cat_max_default_compare())
{
    return ::srook::algorithm::cat_max(range.cbegin(), range.cend(), pred);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
#endif
