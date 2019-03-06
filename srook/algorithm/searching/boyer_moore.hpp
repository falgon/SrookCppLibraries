// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_BOYER_MOORE_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_BOYER_MOORE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/searching/detail/config.hpp>
#include <srook/algorithm/searching/detail/bm_traits.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/disable_if.hpp>
#include <srook/type_traits/is_convertible.hpp>
#include <cassert>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

class boyer_moore_performer_impl {
protected:
    template <class SkipTable, typename DiffType, class PatternIterator, class CorpusIterator>
    static SROOK_FORCE_INLINE CorpusIterator 
    do_search(const SkipTable& skip, const std::vector<DiffType>& suffix, PatternIterator first_, DiffType pattern_length, CorpusIterator corpus_first, CorpusIterator corpus_last)
    {
        typedef DiffType difference_type;

        CorpusIterator corpus_position = corpus_first;
        std::advance(corpus_last, -pattern_length);

        for (difference_type j, k, m; corpus_position <= corpus_last;) {
            j = pattern_length;
            while (*std::next(first_, j - 1) == *std::next(corpus_position, j - 1)) {
                    --j;
                    if (!j) return corpus_position;
            }
            k = skip[*std::next(corpus_position, j - 1)];
            m = j - k - 1;
            if (k < j && m > suffix[j]) corpus_position += m;
            else corpus_position += suffix[j];
        }
        return corpus_last;
    }
};

#if SROOK_HAS_CPP_CONCEPTS
#   define SROOK_BOYER_MOORE_CONCEPTS_ITERATOR srook::concepts::ForwardIterator 
#else
#   define SROOK_BOYER_MOORE_CONCEPTS_ITERATOR class
#endif

template <class, class>
class boyer_moore_performer SROOK_FINAL : protected boyer_moore_performer_impl {
public:
    template <class SkipTable, typename DiffType, class PatternIterator, class CorpusIterator>
    SROOK_DEPRECATED_MESSAGE("It is possible to use this algorithm with non-random-access-iterator, but access to each element is inefficient because it is not a constant time.")
    static SROOK_FORCE_INLINE CorpusIterator
    do_search(const SkipTable& skip, const std::vector<DiffType>& suffix, PatternIterator first_, DiffType pattern_length, CorpusIterator corpus_first, CorpusIterator corpus_last)
    {
        return boyer_moore_performer_impl::do_search(skip, suffix, first_, pattern_length, corpus_first, corpus_last);
    }
};

template <>
class boyer_moore_performer<std::random_access_iterator_tag, std::random_access_iterator_tag> SROOK_FINAL : protected boyer_moore_performer_impl {
public:
    using boyer_moore_performer_impl::do_search;
};

template <class T, class U>
struct boyer_moore_difference_max_type : public conditional<sizeof(T) < sizeof(U), U, T> {};

} // namespace detail

template <class PatternIterator, class traits = detail::BM_traits<PatternIterator>>
class boyer_moore {
    typedef std::iterator_traits<PatternIterator> iterator_traits;
    typedef SROOK_DEDUCED_TYPENAME iterator_traits::difference_type difference_type;
public:
    SROOK_CONSTEXPR boyer_moore(PatternIterator first, PatternIterator last) 
        : first_(first), last_(last), pattern_length(std::distance(first, last)), skip(pattern_length, -1), suffix(pattern_length + 1, 0)
    {
        build_skip_table();
        build_suffix_table();
    }

    template <SROOK_BOYER_MOORE_CONCEPTS_ITERATOR CorpusIterator>
    SROOK_FORCE_INLINE CorpusIterator operator()(CorpusIterator corpus_first, CorpusIterator corpus_last) const
    {
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<CorpusIterator>::value_type corpus_value_type;
        SROOK_STATIC_ASSERT((is_convertible<SROOK_DEDUCED_TYPENAME iterator_traits::value_type, corpus_value_type>::value), "The value of the range must be convertible");

        if (corpus_first == corpus_last) return corpus_last;
        if (first_ == last_) return corpus_first;
        if (std::distance(corpus_first, corpus_last) < pattern_length) return corpus_last;

        typedef SROOK_DEDUCED_TYPENAME iterator_traits::iterator_category pattern_iter_category;
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<CorpusIterator>::iterator_category corpus_iter_category;
        return detail::boyer_moore_performer<pattern_iter_category, corpus_iter_category>::do_search(skip, suffix, first_, pattern_length, corpus_first, corpus_last);
    }
private:
    SROOK_FORCE_INLINE void build_skip_table() 
    {
        PatternIterator f_ = first_;
        for (std::size_t i = 0; f_ != last_; ++f_, ++i) skip.insert(*f_, i);
    }
    SROOK_FORCE_INLINE void build_suffix_table() 
    {
        if (pattern_length > 0) {
            std::vector<SROOK_DEDUCED_TYPENAME iterator_traits::value_type> reversed(pattern_length);
            std::reverse_copy(first_, last_, reversed.begin());
            std::vector<difference_type> prefix(pattern_length, 0);
            compute_bm_prefix(prefix);
            std::vector<difference_type> prefix_reversed(pattern_length, 0);
            compute_bm_prefix(prefix_reversed);
            
            for (difference_type i = 0; i <= pattern_length; ++i) suffix[i] = pattern_length - prefix [pattern_length-1];
            
            for (difference_type i = 0; i < pattern_length; ++i) {
                const difference_type j = pattern_length - prefix_reversed[i], k = i - prefix_reversed[i] + 1;
                if (suffix[j] > k) suffix[j] = k;
            }
        }
    }
    SROOK_FORCE_INLINE void compute_bm_prefix(std::vector<difference_type>& prefix)
    {
        assert(pattern_length > 0);
        typedef SROOK_DEDUCED_TYPENAME detail::boyer_moore_difference_max_type<SROOK_DEDUCED_TYPENAME std::vector<difference_type>::size_type, difference_type>::type diff_max_type;
        assert(static_cast<diff_max_type>(prefix.size()) == static_cast<diff_max_type>(pattern_length));

        difference_type k = 0;
        for (difference_type i = 1; i < pattern_length; ++i) {
            assert(k < pattern_length);
            while (k > 0 && *std::next(first_, k) != *std::next(first_, i)) {
                assert(k < pattern_length);
                k = prefix[k + 1];
            }
            if (*std::next(first_, k) == *std::next(first_, i)) ++k;
            prefix[i] = k;
        }
    }
private:   
    PatternIterator first_, last_;
    const difference_type pattern_length;
    SROOK_DEDUCED_TYPENAME traits::skip_table_t skip;
    std::vector<difference_type> suffix;
};

#if SROOK_CPP_DEDUCTION_GUIDES
template <class PatternIterator>
boyer_moore(PatternIterator, PatternIterator) -> boyer_moore<PatternIterator>;
#endif

template <SROOK_BOYER_MOORE_CONCEPTS_ITERATOR PatternIterator, SROOK_BOYER_MOORE_CONCEPTS_ITERATOR CorpusIterator>
SROOK_FORCE_INLINE CorpusIterator boyer_moore_search(PatternIterator pattern_first, PatternIterator pattern_last, CorpusIterator corpus_first, CorpusIterator corpus_last)
{
    return boyer_moore<PatternIterator>(pattern_first, pattern_last)(corpus_first, corpus_last);
}

template <class PatternRange, SROOK_BOYER_MOORE_CONCEPTS_ITERATOR CorpusIterator>
SROOK_FORCE_INLINE CorpusIterator boyer_moore_search(CorpusIterator corpus_first, CorpusIterator corpus_last, const PatternRange &pattern)
{
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
    typedef SROOK_DEDUCED_TYPENAME boost::range_iterator<const PatternRange>::type pattern_iterator;
    using boost::begin;
    using boost::end;
#else
    typedef SROOK_DEDUCED_TYPENAME srook::range_iterator<const PatternRange>::type pattern_iterator;
    using std::begin;
    using std::end;
#endif
    return boyer_moore<pattern_iterator>(begin(pattern), end(pattern))(corpus_first, corpus_last);
}

  
template <SROOK_BOYER_MOORE_CONCEPTS_ITERATOR PatternIterator, class CorpusRange>
SROOK_FORCE_INLINE
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
SROOK_DEDUCED_TYPENAME boost::lazy_disable_if_c<is_same<CorpusRange, PatternIterator>::value, SROOK_DEDUCED_TYPENAME boost::range_iterator<CorpusRange>>::type
boyer_moore_search(CorpusRange& corpus, PatternIterator pat_first, PatternIterator pat_last)
{
    return boyer_moore<PatternIterator>(pat_first, pat_last)(boost::begin(corpus), boost::end(corpus));
}
#else
SROOK_DEDUCED_TYPENAME disable_if<is_same<CorpusRange, PatternIterator>::value, SROOK_DEDUCED_TYPENAME srook::range_iterator<CorpusRange>>::type
boyer_moore_search(CorpusRange& corpus, PatternIterator pat_first, PatternIterator pat_last)
{
    return boyer_moore<PatternIterator>(pat_first, pat_last)(std::begin(corpus), std::end(corpus));
}
#endif
 
template <class PatternRange, class CorpusRange>
SROOK_FORCE_INLINE
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
SROOK_DEDUCED_TYPENAME boost::range_iterator<CorpusRange>::type
boyer_moore_search(CorpusRange& corpus, const PatternRange& pattern)
{
    typedef SROOK_DEDUCED_TYPENAME boost::range_iterator<const PatternRange>::type pattern_iterator;
    return boyer_moore<pattern_iterator>(boost::begin(pattern), boost::end(pattern))(boost::begin(corpus), boost::end(corpus));
}
#else
SROOK_DEDUCED_TYPENAME srook::range_iterator<CorpusRange>::type
boyer_moore_search(CorpusRange& corpus, const PatternRange& pattern)
{
    typedef SROOK_DEDUCED_TYPENAME srook::range_iterator<const PatternRange>::type pattern_iterator;
    return boyer_moore<pattern_iterator>(std::begin(pattern), std::end(pattern))(std::begin(corpus), std::end(corpus));
}
#endif

template <class Range>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
boyer_moore<SROOK_DEDUCED_TYPENAME boost::range_iterator<const Range>::type>
make_boyer_moore(const Range& r) 
{
    return boyer_moore<SROOK_DEDUCED_TYPENAME boost::range_iterator<const Range>::type>(boost::begin(r), boost::end(r));
}
#else
boyer_moore<SROOK_DEDUCED_TYPENAME srook::range_iterator<const Range>::type>
make_boyer_moore(const Range& r)
{
    return boyer_moore<SROOK_DEDUCED_TYPENAME srook::range_iterator<const Range>::type>(std::begin(r), std::end(r));
}
#endif

template <class Range>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
boyer_moore<SROOK_DEDUCED_TYPENAME boost::range_iterator<Range>::type>
make_boyer_moore(Range &r) 
{
    return boyer_moore<SROOK_DEDUCED_TYPENAME boost::range_iterator<Range>::type>(boost::begin(r), boost::end(r));
}
#else
boyer_moore<SROOK_DEDUCED_TYPENAME srook::range_iterator<Range>::type>
make_boyer_moore(Range& r)
{
    return boyer_moore<SROOK_DEDUCED_TYPENAME boost::range_iterator<Range>::type>(std::begin(r), std::end(r));
}
#endif

#undef SROOK_BOYER_MOORE_CONCEPTS_ITERATOR

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
