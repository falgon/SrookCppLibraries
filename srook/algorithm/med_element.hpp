//  Copyright (C) 2011-2018 Roki. Distributed under the MIT License
/**
 * @file med_element.hpp
 * @brief Finds the median element in the range [first, last).
 * @author roki
 * @date 2018 02 11
 */

#ifndef INCLUDED_SROOK_ALGORITHM_MED_ELEMENT_HPP
#define INCLUDED_SROOK_ALGORITHM_MED_ELEMENT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cxx20/concepts/iterator/RandomAccessIterator.hpp>
#include <srook/type_traits/iterator/is_randomaccessiterator.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

/**
 * @return bool
 * @param (x) the random access iterator.
 * @param (y) the random access iterator.
 * @param (comp) compare functional object.
 * @details Compare object for med_element. 
 */
template <class Iter, class Compare> 
struct med_element_comp {
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR bool f(Iter x, Iter y, Compare comp) 
    SROOK_NOEXCEPT(Compare(*declval<Iter&>(), *declval<Iter&>()))
    {    
        return comp(*x, *y); 
    }
};

} // namespace detail


/**
 *
 * @fn
 * 
 *
 * @return Iterator to the median element in the range [first, last). If several elements in the range are equivalent to the smallest element, returns the iterator to the first such element. Returns last if the range is empty.
 * 
 * @param (first) the random access iterator defining first of the range to examine
 * @param (last) the random access iterator defining last of the range to examine
 * 
 * @detailsFinds the median element in the range [first, last). Elements are compared using the given binary comparison function comp. The time complexity is O(N). The space complexity is O(N). 
 *
 */

#if SROOK_HAS_CONCEPTS
template <srook::concepts::RandomAccessIterator RandomAccessIter, class Compare>
#else
template <class RandomAccessIter, class Compare>
#endif
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<
        is_randomaccessiterator<RandomAccessIter>, 
        is_invocable<
            Compare, 
            SROOK_DEDUCED_TYPENAME std::iterator_traits<RandomAccessIter>::value_type,
            SROOK_DEDUCED_TYPENAME std::iterator_traits<RandomAccessIter>::value_type
        >
    >::value,
    RandomAccessIter
>::type
med_element(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
    //! Copy to not affect the original range.
    std::vector<RandomAccessIter> v(std::distance(first, last));
    {
        SROOK_DEDUCED_TYPENAME std::vector<RandomAccessIter>::iterator viter = srook::begin(v);
        for (SROOK_DEDUCED_TYPENAME std::vector<RandomAccessIter>::iterator it = srook::begin(v); first != last;) 
            *viter++ = first++;
    }
    auto f = std::bind(detail::med_element_comp<RandomAccessIter, Compare>::f, std::placeholders::_1, std::placeholders::_2, comp);
    std::nth_element(srook::begin(v), std::next(srook::begin(v), v.size() / 2), srook::end(v), srook::move(f));
    return v[v.size() / 2];
}

/**
 *
 * @fn
 * Finds the median element in the range [first, last). Elements are compared using operator<.
 *
 * @return Iterator to the median element in the range [first, last). If several elements in the range are equivalent to the smallest element, returns the iterator to the first such element. Returns last if the range is empty.
 * 
 * @param (first) Random access iterators defining first of the range to examine
 * @param (last) Random access iterators defining last of the range to examine
 * 
 * @detail The time complexity is O(N). The space complexity is O(N).
 *
 */

#if SROOK_HAS_CONCEPTS
template <srook::concepts::RandomAccessIterator RandomAccessIter>
#else
template <class RandomAccessIter>
#endif
SROOK_FORCE_INLINE RandomAccessIter med_element(RandomAccessIter first, RandomAccessIter last)
{
    return med_element(first, last, std::less<SROOK_DEDUCED_TYPENAME std::iterator_traits<RandomAccessIter>::value_type>());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)
#endif
