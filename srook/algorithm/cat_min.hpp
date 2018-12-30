// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_CAT_MIN_HPP
#define INCLUDED_SROOK_ALGORITHM_CAT_MIN_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/cat_max.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

struct cat_min_default_compare {
    template <class T>
    SROOK_FORCE_INLINE bool operator()(T l, T r)
    {
        return !::srook::algorithm::detail::cat_max_default_compare()(l, r);
    }
};

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator InputIter, class Predicate = detail::cat_min_default_compare>
#else
template <class InputIter, class Predicate = detail::cat_min_default_compare>
#endif
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        is_invocable<Predicate, SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type, SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type>,
        is_inputiterator<InputIter>, 
        is_arithmetic<SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type>
    >::value, 
    SROOK_DEDUCED_TYPENAME std::iterator_traits<InputIter>::value_type
>::type
cat_min(InputIter first, InputIter last, Predicate pred = detail::cat_min_default_compare())
{
    return ::srook::algorithm::cat_max(first, last, pred);
}

template <class SinglePassRange, class Predicate = detail::cat_min_default_compare>
SROOK_DEDUCED_TYPENAME disable_if<is_iterator<SinglePassRange>::value, SROOK_DEDUCED_TYPENAME SinglePassRange::value_type>::type
cat_min(const SinglePassRange& range, Predicate pred = detail::cat_min_default_compare())
{
    return ::srook::algorithm::cat_min(range.cbegin(), range.cend(), pred);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
#endif
