// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_LCS_HPP
#define INCLUDED_SROOK_ALGORITHM_LCS_HPP
#include <srook/algorithm/searching/longest_common_subsequence.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

template <class ForwardIterator1, class ForwardIterator2>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
enable_if<
    is_convertible<
        SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator1>::value_type, 
        SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator2>::value_type
    >::value, 
    std::pair<ForwardIterator1, ForwardIterator1>
>::type
lcs(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
{
    return longest_common_subsequence<ForwardIterator1>(first1, last1)(first2, last2);
}

template <class ForwardIterator1, class Range>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        is_convertible<
            SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator1>::value_type,
            SROOK_DEDUCED_TYPENAME Range::value_type
        >,
        type_traits::detail::Lnot<is_same<ForwardIterator1, Range>>
    >::value,
    std::pair<ForwardIterator1, ForwardIterator1>
>::type
lcs(ForwardIterator1 first1, ForwardIterator1 last1, const Range& range)
{
    return longest_common_subsequence<ForwardIterator1>(first1, last1)(std::begin(range), std::end(range));
}

template <class Range, class ForwardIterator2>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        is_convertible<
            SROOK_DEDUCED_TYPENAME Range::value_type,
            SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator2>::value_type
        >,
        type_traits::detail::Lnot<is_same<Range, ForwardIterator2>>
    >::value,
    std::pair<SROOK_DECLTYPE(std::begin(declval<Range>())), SROOK_DECLTYPE(std::end(declval<Range>()))>
>::type
lcs(const Range& range, ForwardIterator2 first2, ForwardIterator2 last2)
{
    typedef SROOK_DECLTYPE(std::begin(declval<Range>())) iter_type;
    return longest_common_subsequence<iter_type>(std::begin(range), std::end(range))(first2, last2);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
