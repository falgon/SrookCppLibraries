// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_LONGEST_COMMON_SUBSEQUENCE_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_LONGEST_COMMON_SUBSEQUENCE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <vector>

namespace srook {
namespace algorithm {
SROOK_INLINE_NAMESPACE(v1)

/*
 *
 * generic function longest common subsequence (lcs).
 *
 * This function is implemented by DP.
 *
 * R1 -> std::distance(first1, last1)
 * R2 -> std::distance(first2, last2)
 * computational complexity: O(R1 * R2)
 * 
 */

namespace detail {

class longest_common_subsequence_performer_impl {
protected:
#if SROOK_HAS_CONCEPTS
    template <typename DiffType, srook::concepts::ForwardIterator ForwardIterator1, srook::concepts::ForwardIterator ForwardIterator2> 
#else
    template <typename DiffType, class ForwardIterator1, class ForwardIterator2>
#endif
    static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
    enable_if<
        is_convertible<
            SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator1>::value_type, 
            SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator2>::value_type
        >::value, 
        std::pair<ForwardIterator1, ForwardIterator1>
    >::type
    do_search(ForwardIterator1 first1, ForwardIterator1 last1, DiffType leftrange_size, ForwardIterator2 first2, ForwardIterator2 last2)
    {
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator2>::difference_type size_type;
        typedef std::vector<size_type> vector;

        const size_type rightrange_size = std::distance(first2, last2);
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

        ForwardIterator1 result_end = std::next(first1, row);
        for (; length_table[col * tb_x + row] != 0; --row, --col);

        return std::make_pair(std::next(first1, row), result_end);
    }
};

template <class, class>
class longest_common_subsequence_performer SROOK_FINAL : protected longest_common_subsequence_performer_impl {
public:
    template <typename DiffType, class ForwardIterator1, class ForwardIterator2>
    SROOK_DEPRECATED_MESSAGE("It is possible to use this algorithm with non-random-access-iterator, but access to each element is inefficient because it is not a constant time.")
    static SROOK_FORCE_INLINE std::pair<ForwardIterator1, ForwardIterator2> 
    do_search(ForwardIterator1 first1, ForwardIterator1 last1, DiffType distance, ForwardIterator2 first2, ForwardIterator2 last2)
    {
        return longest_common_subsequence_performer_impl::do_search(first1, last1, distance, first2, last2);
    }
};

template <>
class longest_common_subsequence_performer<std::random_access_iterator_tag, std::random_access_iterator_tag> SROOK_FINAL : protected longest_common_subsequence_performer_impl {
public:
    using longest_common_subsequence_performer_impl::do_search;
};

template <class, class = SROOK_DEDUCED_TYPENAME voider<>::type>
struct is_accessible_iterator_category : SROOK_FALSE_TYPE {};
template <class T>
struct is_accessible_iterator_category<T, SROOK_DEDUCED_TYPENAME voider<SROOK_DEDUCED_TYPENAME T::iterator_category>::type> : SROOK_TRUE_TYPE {};

} // namespace detail

template <class ForwardIterator1>
class longest_common_subsequence {
    typedef std::iterator_traits<ForwardIterator1> iterator_traits;
    typedef SROOK_DEDUCED_TYPENAME iterator_traits::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME iterator_traits::difference_type difference_type;
    typedef SROOK_DEDUCED_TYPENAME iterator_traits::iterator_category iterator_category;
public:
    SROOK_CONSTEXPR longest_common_subsequence(ForwardIterator1 first, ForwardIterator1 last) : first_(first), last_(last), distance_(std::distance(first_, last_)) {}

#ifdef SROOK_HAS_CONCEPTS
    SROOK_ST_ASSERT(srook::concepts::ForwardIterator<ForwardIterator1>);
    template <srook::concepts::ForwardIterator ForwardIterator2> 
#else
    template <class ForwardIterator2>
#endif
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
    enable_if<
        is_convertible<value_type, SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator2>::value_type>::value, 
        std::pair<ForwardIterator1, ForwardIterator1>
    >::type
    operator()(ForwardIterator2 first2, ForwardIterator2 last2)
    {
        if (first_ == first2 && last_ == last2) return std::make_pair(first_, last_);
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator2>::iterator_category fiter2_category;
        return detail::longest_common_subsequence_performer<iterator_category, fiter2_category>::do_search(first_, last_, distance_, first2, last2);
    }
private:
    ForwardIterator1 first_, last_;
    difference_type distance_;
};

#if SROOK_CPP_DEDUCTION_GUIDES
template <class ForwardIterator>
longest_common_subsequence(ForwardIterator, ForwardIterator) -> longest_common_subsequence<ForwardIterator>;
#endif

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIterator1, srook::concepts::ForwardIterator ForwardIterator2>
#else
template <class ForwardIterator1, class ForwardIterator2>
#endif
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
enable_if<
    is_convertible<
        SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator1>::value_type, 
        SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator2>::value_type
    >::value, 
    std::pair<ForwardIterator1, ForwardIterator1>
>::type
longest_common_subsequence_search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
{
    return longest_common_subsequence<ForwardIterator1>(first1, last1)(first2, last2);
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIterator1, class Range>
#else
template <class ForwardIterator1, class Range>
#endif
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
longest_common_subsequence_search(ForwardIterator1 first1, ForwardIterator1 last1, const Range& range)
{
    return longest_common_subsequence<ForwardIterator1>(first1, last1)(std::begin(range), std::end(range));
}

#if SROOK_HAS_CONCEPTS
template <class Range, srook::concepts::ForwardIterator ForwardIterator2>
#else
template <class Range, class ForwardIterator2>
#endif
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
longest_common_subsequence_search(const Range& range, ForwardIterator2 first2, ForwardIterator2 last2)
{
    typedef SROOK_DECLTYPE(std::begin(declval<Range>())) iter_type;
    return longest_common_subsequence<iter_type>(std::begin(range), std::end(range))(first2, last2);
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIterator>
#else
template <class ForwardIterator>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME enable_if<detail::is_accessible_iterator_category<std::iterator_traits<ForwardIterator>>::value, longest_common_subsequence<ForwardIterator>>::type
make_longest_common_subsequence(ForwardIterator first, ForwardIterator last) SROOK_NOEXCEPT_TRUE
{
    return longest_common_subsequence<ForwardIterator>(first, last);
}

template <class Range>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<
    detail::is_accessible_iterator_category<std::iterator_traits<SROOK_DEDUCED_TYPENAME Range::iterator>>::value, 
    longest_common_subsequence<SROOK_DECLTYPE(std::begin(declval<Range>()))>
>::type
make_longest_common_subsequence(const Range& range)
{
    typedef SROOK_DECLTYPE(std::begin(declval<Range>())) iter_type;
    return longest_common_subsequence<iter_type>(std::begin(range), std::end(range));
}

SROOK_INLINE_NAMESPACE_END
} // namespace algorithm
} // namespace srook

#endif
