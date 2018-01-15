// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_LCS_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_LCS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <vector>

namespace srook {
namespace algorithm {
SROOK_INLINE_NAMESPACE(v1)

/*
 *
 * generic function longest common substring (lcs).
 *
 * This function is implemented by DP.
 *
 * R1 -> std::distance(first1, last1)
 * R2 -> std::distance(first2, last2)
 * computational complexity: O(R1 * R2)
 * 
 */

#ifdef SROOK_ENABLE_CONCEPTS
template <srook::concepts::Iterator ForwardIteartor1, srook::concepts::Iterator ForwardIterator2> 
#else
template <class ForwardIteartor1, class ForwardIterator2>
#endif
SROOK_DEDUCED_TYPENAME 
enable_if<
    is_convertible<
        SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIteartor1>::value_type, 
        SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator2>::value_type
    >::value, 
    std::pair<ForwardIteartor1, ForwardIteartor1>
>::type
lcs(ForwardIteartor1 first1, ForwardIteartor1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
{
    if (first1 == first2 && last1 == last2) return std::make_pair(first1, last1);

    typedef std::vector<std::size_t> vector;
    typedef SROOK_DEDUCED_TYPENAME vector::size_type size_type;
    const size_type leftrange_size = std::distance(first1, last1), rightrange_size = std::distance(first2, last2);
    const size_type tb_x = leftrange_size + 1, tb_y = rightrange_size + 1;

    vector length_table(tb_x * tb_y, 0);
    size_type len = 0, row = 0, col = 0;

    for(size_type i = 0; i <= leftrange_size; ++i) {
        for(size_type j = 0; j <= rightrange_size; ++j) {
            if (!((!i) || (!j)) && *std::next(first1, i - 1) == *std::next(first2, j - 1)) {
                length_table[j * tb_x + i] = length_table[(j - 1) * tb_x + (i - 1)] + 1;
                if (len < length_table[j * tb_x + i]) {
                    len = length_table[j * tb_x + i];
                    row = i;
                    col = j;
                }
            } 
        }
    }

    if (!len) return std::make_pair(last1, last1);

    ForwardIteartor1 result_end = std::next(first1, row);
    for (; length_table[col * tb_x + row] != 0; --row, --col);

    return std::make_pair(std::next(first1, row), result_end);
}

SROOK_INLINE_NAMESPACE_END
} // namespace algorithm

using algorithm::lcs;

} // namespace srook

#endif
