// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCH_KNUTH_MORRIS_PRATT_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCH_KNUTH_MORRIS_PRATT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/searching/detail/config.hpp>
#include <srook/type_traits/is_convertible.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/disable_if.hpp>
#include <vector>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

class knuth_morris_pratt_performer_impl {
protected:
    template <class DiffType, class PatternIterator, class CorpusIterator>
    SROOK_FORCE_INLINE static CorpusIterator 
    do_search(const std::vector<DiffType>& skip, PatternIterator pat_first, DiffType pat_length, CorpusIterator corpus_first, CorpusIterator corpus_last, DiffType corpus_length)
    {
        typedef DiffType difference_type;

        difference_type match_start = 0;
        const difference_type last_match = corpus_length - pat_length;
        for (difference_type idx = 0; match_start <= last_match;) {
            while (*std::next(pat_first, idx) == *std::next(corpus_first, match_start + idx)) {
                if (++idx == pat_length) return std::next(corpus_first, match_start);
            }
            match_start += idx - skip[idx];
            idx = skip[idx] >= 0 ? skip[idx] : 0;
        }
        return corpus_last;
    }
};
   
template <class, class>
class knuth_morris_pratt_performer SROOK_FINAL : protected knuth_morris_pratt_performer_impl {
public:
    template <typename DiffType, class PatternIterator, class CorpusIterator>
    SROOK_DEPRECATED_MESSAGE("It is possible to use this algorithm with non-random-access-iterator, but access to each element is inefficient because it is not a constant time.")
    SROOK_FORCE_INLINE static CorpusIterator 
    do_search(const std::vector<DiffType>& skip, PatternIterator pat_first, DiffType pat_length, CorpusIterator corpus_first, CorpusIterator corpus_last, DiffType corpus_length)
    {
        return knuth_morris_pratt_performer_impl::do_search(skip, pat_first, pat_length, corpus_first, corpus_last, corpus_length);
    }
};

template <>
class knuth_morris_pratt_performer<std::random_access_iterator_tag, std::random_access_iterator_tag> SROOK_FINAL : protected knuth_morris_pratt_performer_impl {
public:
    using knuth_morris_pratt_performer_impl::do_search;
};

} // namespace detail

template <class PatternIterator>
class knuth_morris_pratt {
    typedef std::iterator_traits<PatternIterator> pattern_traits;
    typedef SROOK_DEDUCED_TYPENAME pattern_traits::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME pattern_traits::iterator_category iterator_category;
    typedef SROOK_DEDUCED_TYPENAME pattern_traits::difference_type difference_type;
public:
    SROOK_CONSTEXPR knuth_morris_pratt(PatternIterator first, PatternIterator last)
        : pat_first(first), pat_last(last), pat_length(std::distance(pat_first, pat_last)), skip(pat_length + 1, -1)
    {
        compute_prefix();
    }

    template <class CorpusIterator>
    CorpusIterator operator()(CorpusIterator corpus_first, CorpusIterator corpus_last) const
    {
        typedef std::iterator_traits<CorpusIterator> corpus_traits;
        typedef SROOK_DEDUCED_TYPENAME corpus_traits::value_type corpus_value_type;
        SROOK_STATIC_ASSERT((is_convertible<value_type, corpus_value_type>::value), "The value of the range must be convertible");

        if (corpus_first == corpus_last) return corpus_last;
        if (pat_first == pat_last) return corpus_first;
        
        const difference_type corpus_length = std::distance(corpus_first, corpus_last);
        if (corpus_length < pat_length) return corpus_last;
        
        typedef SROOK_DEDUCED_TYPENAME corpus_traits::iterator_category corpus_iter_category;
        return detail::knuth_morris_pratt_performer<iterator_category, corpus_iter_category>::do_search(skip, pat_first, pat_length, corpus_first, corpus_last, corpus_length);
    }
private:
    SROOK_FORCE_INLINE void compute_prefix()
    {
        for (difference_type i = 1, j; i <= pat_length; ++i) {
            j = skip[i - 1];
            while (j >= 0) {
                if (*std::next(pat_first, j) == *std::next(pat_first, i - 1)) break;
                j = skip[j];
            }
            skip[i] = j + 1;
        }
    }
private:
    PatternIterator pat_first, pat_last;
    const difference_type pat_length;
    std::vector<difference_type> skip;
};

#if SROOK_CPP_DEDUCTION_GUIDES
template <class PatternIterator>
knuth_morris_pratt(PatternIterator, PatternIterator) -> knuth_morris_pratt<PatternIterator>;
#endif

#if SROOK_HAS_CPP_CONCEPTS
#   define SROOK_KNUTH_MORRIS_PRATT_CONCEPTS_ITERATOR srook::concepts::ForwardIterator 
#else
#   define SROOK_KNUTH_MORRIS_PRATT_CONCEPTS_ITERATOR class
#endif

template <SROOK_KNUTH_MORRIS_PRATT_CONCEPTS_ITERATOR CorpusIterator, SROOK_KNUTH_MORRIS_PRATT_CONCEPTS_ITERATOR PatternIterator>
SROOK_FORCE_INLINE CorpusIterator 
knuth_morris_pratt_search(CorpusIterator corpus_first, CorpusIterator corpus_last, PatternIterator pattern_first, PatternIterator pattern_last)
{
    return srook::algorithm::knuth_morris_pratt<PatternIterator>(pattern_first, pattern_last)(corpus_first, corpus_last);
}

template <class PatternRange, SROOK_KNUTH_MORRIS_PRATT_CONCEPTS_ITERATOR CorpusIterator>
SROOK_FORCE_INLINE CorpusIterator
knuth_morris_pratt_search(CorpusIterator corpus_first, CorpusIterator corpus_last, const PatternRange& pattern)
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
    return knuth_morris_pratt<pattern_iterator>(begin(pattern), end(pattern))(corpus_first, corpus_last);
}

template <SROOK_KNUTH_MORRIS_PRATT_CONCEPTS_ITERATOR PatternIterator, class CorpusRange>
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
SROOK_DEDUCED_TYPENAME boost::lazy_disable_if_c<is_same<CorpusRange, PatternIterator>::value, boost::range_iterator<CorpusRange>>::type
knuth_morris_pratt_search(CorpusRange& corpus, PatternIterator pat_first, PatternIterator pat_last)
{
    return knuth_morris_pratt<PatternIterator>(pat_first, pat_last)(boost::begin(corpus), boost::end(corpus));
}
#else
SROOK_DEDUCED_TYPENAME disable_if<is_same<CorpusRange, PatternIterator>::value, srook::range_iterator<CorpusRange>>::type
knuth_morris_pratt_search(CorpusRange& corpus, PatternIterator pat_first, PatternIterator pat_last)
{
    return knuth_morris_pratt<PatternIterator>(pat_first, pat_last)(std::begin(corpus), std::end(corpus));
}
#endif

template <class PatternRange, class CorpusRange>
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
SROOK_DEDUCED_TYPENAME boost::range_iterator<CorpusRange>::type
knuth_morris_pratt_search(CorpusRange& corpus, const PatternRange& pattern)
{
    typedef SROOK_DEDUCED_TYPENAME boost::range_iterator<const PatternRange>::type pattern_iterator;
    return knuth_morris_pratt<pattern_iterator>(boost::begin(pattern), boost::end(pattern))(boost::begin(corpus), boost::end(corpus));
}
#else
SROOK_DEDUCED_TYPENAME srook::range_iterator<CorpusRange>::type
knuth_morris_pratt_search(CorpusRange& corpus, const PatternRange& pattern)
{
    typedef SROOK_DEDUCED_TYPENAME srook::range_iterator<const PatternRange>::type pattern_iterator;
    return knuth_morris_pratt<pattern_iterator>(std::begin(pattern), std::end(pattern))(std::begin(corpus), std::end(corpus));
}
#endif

template <class Range>
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
SROOK_DEDUCED_TYPENAME srook::algorithm::knuth_morris_pratt<SROOK_DEDUCED_TYPENAME boost::range_iterator<const Range>::type>
make_knuth_morris_pratt(const Range& range)
{
    return srook::algorithm::knuth_morris_pratt<SROOK_DEDUCED_TYPENAME boost::range_iterator<const Range>::type>(boost::begin(range), boost::end(range));
}
#else
SROOK_DEDUCED_TYPENAME srook::algorithm::knuth_morris_pratt<SROOK_DEDUCED_TYPENAME srook::range_iterator<const Range>::type>
make_knuth_morris_pratt(const Range& range)
{
    return srook::algorithm::knuth_morris_pratt<SROOK_DEDUCED_TYPENAME srook::range_iterator<const Range>::type>(std::begin(range), std::end(range));
}
#endif

template <class Range>
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
SROOK_DEDUCED_TYPENAME srook::algorithm::knuth_morris_pratt<SROOK_DEDUCED_TYPENAME boost::range_iterator<Range>::type>
make_knuth_morris_pratt(Range& r)
{
    return srook::algorithm::knuth_morris_pratt<SROOK_DEDUCED_TYPENAME boost::range_iterator<Range>::type>(boost::begin(r), boost::end(r));
}
#else
SROOK_DEDUCED_TYPENAME srook::algorithm::knuth_morris_pratt<SROOK_DEDUCED_TYPENAME srook::range_iterator<Range>::type>
make_knuth_morris_pratt(Range& r)
{
    return srook::algorithm::knuth_morris_pratt<SROOK_DEDUCED_TYPENAME srook::range_iterator<Range>::type>(std::begin(r), std::end(r));
}
#endif

#undef SROOK_KNUTH_MORRIS_PRATT_CONCEPTS_ITERATOR

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
