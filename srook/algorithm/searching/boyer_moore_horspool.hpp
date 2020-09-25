// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_BOYER_MOORE_HORSPOOL_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_BOYER_MOORE_HORSPOOL_HPP

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

class boyer_moore_horspool_performer_impl {
protected:
    template <class SkipTable, typename DiffType, class PatternIterator, class CorpusIterator>
    static SROOK_FORCE_INLINE CorpusIterator 
    do_search(const SkipTable& skip, PatternIterator first_, DiffType pattern_length, CorpusIterator corpus_first, CorpusIterator corpus_last)
    {
        CorpusIterator first_position = corpus_first;
        const CorpusIterator last_position = std::next(corpus_last, -pattern_length);
        while (first_position <= last_position) {
            DiffType j = pattern_length - 1;
            while (*std::next(first_, j) == *std::next(first_position, j)) {
                if (!j) return first_position;
                --j;
            }
            std::advance(first_position, skip[*std::next(first_position, pattern_length - 1)]);
        }
        return corpus_last;
    }
};

#if SROOK_HAS_CPP_CONCEPTS
#   define SROOK_BOYER_MOORE_HORSPOOL_CONCEPTS_ITERATOR srook::concepts::ForwardIterator 
#else
#   define SROOK_BOYER_MOORE_HORSPOOL_CONCEPTS_ITERATOR class
#endif

template <class, class>
class boyer_moore_horspool_performer SROOK_FINAL : protected boyer_moore_horspool_performer_impl {
public:
    template <class SkipTable, typename DiffType, class PatternIterator, class CorpusIterator>
    SROOK_DEPRECATED_MESSAGE("It is possible to use this algorithm with non-random-access-iterator, but access to each element is inefficient because it is not a constant time.")
    static SROOK_FORCE_INLINE CorpusIterator
    do_search(const SkipTable& skip, PatternIterator first_, DiffType pattern_length, CorpusIterator corpus_first, CorpusIterator corpus_last)
    {
        return boyer_moore_horspool_performer_impl::do_search(skip, first_, pattern_length, corpus_first, corpus_last);
    }
};

template <>
class boyer_moore_horspool_performer<std::random_access_iterator_tag, std::random_access_iterator_tag> SROOK_FINAL : protected boyer_moore_horspool_performer_impl {
public:
    using boyer_moore_horspool_performer_impl::do_search;
};

template <class T, class U>
struct boyer_moore_horspool_difference_max_type : public conditional<sizeof(T) < sizeof(U), U, T> {};

} // namespace detail

template <class PatternIterator, class traits = detail::BM_traits<PatternIterator>>
class boyer_moore_horspool {
    typedef std::iterator_traits<PatternIterator> iterator_traits;
    typedef SROOK_DEDUCED_TYPENAME iterator_traits::difference_type difference_type;
public:
    SROOK_CONSTEXPR boyer_moore_horspool(PatternIterator first, PatternIterator last) 
        : first_(first), last_(last), pattern_length(std::distance(first, last)), skip(pattern_length, pattern_length)
    {
        build_skip_table();
    }

    template <SROOK_BOYER_MOORE_HORSPOOL_CONCEPTS_ITERATOR CorpusIterator>
    SROOK_FORCE_INLINE CorpusIterator operator()(CorpusIterator corpus_first, CorpusIterator corpus_last) const
    {
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<CorpusIterator>::value_type corpus_value_type;
        SROOK_STATIC_ASSERT((is_convertible<SROOK_DEDUCED_TYPENAME iterator_traits::value_type, corpus_value_type>::value), "The value of the range must be convertible");

        if (corpus_first == corpus_last) return corpus_last;
        if (first_ == last_) return corpus_first;
        if (std::distance(corpus_first, corpus_last) < pattern_length) return corpus_last;

        typedef SROOK_DEDUCED_TYPENAME iterator_traits::iterator_category pattern_iter_category;
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<CorpusIterator>::iterator_category corpus_iter_category;
        return detail::boyer_moore_horspool_performer<pattern_iter_category, corpus_iter_category>::do_search(skip, first_, pattern_length, corpus_first, corpus_last);
    }
private:
    SROOK_FORCE_INLINE void build_skip_table()
    {
        if (first_ != last_) {
            std::size_t i = 0;
            for (PatternIterator iter = first_; iter != std::next(last_, -1); ++iter, ++i) skip.insert(*iter, pattern_length - 1 - i);
        }
    }
private:   
    PatternIterator first_, last_;
    const difference_type pattern_length;
    SROOK_DEDUCED_TYPENAME traits::skip_table_t skip;
};

#if SROOK_CPP_DEDUCTION_GUIDES
template <class PatternIterator>
boyer_moore_horspool(PatternIterator, PatternIterator) -> boyer_moore_horspool<PatternIterator>;
#endif

template <SROOK_BOYER_MOORE_HORSPOOL_CONCEPTS_ITERATOR PatternIterator, SROOK_BOYER_MOORE_HORSPOOL_CONCEPTS_ITERATOR CorpusIterator>
SROOK_FORCE_INLINE CorpusIterator boyer_moore_horspool_search(PatternIterator pattern_first, PatternIterator pattern_last, CorpusIterator corpus_first, CorpusIterator corpus_last)
{
    return boyer_moore_horspool<PatternIterator>(pattern_first, pattern_last)(corpus_first, corpus_last);
}

template <class PatternRange, SROOK_BOYER_MOORE_HORSPOOL_CONCEPTS_ITERATOR CorpusIterator>
SROOK_FORCE_INLINE CorpusIterator boyer_moore_horspool_search(CorpusIterator corpus_first, CorpusIterator corpus_last, const PatternRange &pattern)
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
    return boyer_moore_horspool<pattern_iterator>(begin(pattern), end(pattern))(corpus_first, corpus_last);
}

  
template <SROOK_BOYER_MOORE_HORSPOOL_CONCEPTS_ITERATOR PatternIterator, class CorpusRange>
SROOK_FORCE_INLINE
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
SROOK_DEDUCED_TYPENAME boost::lazy_disable_if_c<is_same<CorpusRange, PatternIterator>::value, SROOK_DEDUCED_TYPENAME boost::range_iterator<CorpusRange>>::type
boyer_moore_horspool_search(CorpusRange& corpus, PatternIterator pat_first, PatternIterator pat_last)
{
    return boyer_moore_horspool<PatternIterator>(pat_first, pat_last)(boost::begin(corpus), boost::end(corpus));
}
#else
SROOK_DEDUCED_TYPENAME disable_if<is_same<CorpusRange, PatternIterator>::value, SROOK_DEDUCED_TYPENAME srook::range_iterator<CorpusRange>>::type
boyer_moore_horspool_search(CorpusRange& corpus, PatternIterator pat_first, PatternIterator pat_last)
{
    return boyer_moore_horspool<PatternIterator>(pat_first, pat_last)(std::begin(corpus), std::end(corpus));
}
#endif
 
template <class PatternRange, class CorpusRange>
SROOK_FORCE_INLINE
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
SROOK_DEDUCED_TYPENAME boost::range_iterator<CorpusRange>::type
boyer_moore_horspool_search(CorpusRange& corpus, const PatternRange& pattern)
{
    typedef SROOK_DEDUCED_TYPENAME boost::range_iterator<const PatternRange>::type pattern_iterator;
    return boyer_moore_horspool<pattern_iterator>(boost::begin(pattern), boost::end(pattern))(boost::begin(corpus), boost::end(corpus));
}
#else
SROOK_DEDUCED_TYPENAME srook::range_iterator<CorpusRange>::type
boyer_moore_horspool_search(CorpusRange& corpus, const PatternRange& pattern)
{
    typedef SROOK_DEDUCED_TYPENAME srook::range_iterator<const PatternRange>::type pattern_iterator;
    return boyer_moore_horspool<pattern_iterator>(std::begin(pattern), std::end(pattern))(std::begin(corpus), std::end(corpus));
}
#endif

template <class Range>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
boyer_moore_horspool<SROOK_DEDUCED_TYPENAME boost::range_iterator<const Range>::type>
make_boyer_moore_horspool(const Range& r) 
{
    return boyer_moore_horspool<SROOK_DEDUCED_TYPENAME boost::range_iterator<const Range>::type>(boost::begin(r), boost::end(r));
}
#else
boyer_moore_horspool<SROOK_DEDUCED_TYPENAME srook::range_iterator<const Range>::type>
make_boyer_moore_horspool(const Range& r)
{
    return boyer_moore_horspool<SROOK_DEDUCED_TYPENAME srook::range_iterator<const Range>::type>(std::begin(r), std::end(r));
}
#endif

template <class Range>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
#if SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR && SROOK_HAS_BOOST_RANGE_BEGIN_HPP && SROOK_HAS_BOOST_RANGE_END_HPP
boyer_moore_horspool<SROOK_DEDUCED_TYPENAME boost::range_iterator<Range>::type>
make_boyer_moore_horspool(Range &r) 
{
    return boyer_moore_horspool<SROOK_DEDUCED_TYPENAME boost::range_iterator<Range>::type>(boost::begin(r), boost::end(r));
}
#else
boyer_moore_horspool<SROOK_DEDUCED_TYPENAME srook::range_iterator<Range>::type>
make_boyer_moore_horspool(Range& r)
{
    return boyer_moore_horspool<SROOK_DEDUCED_TYPENAME boost::range_iterator<Range>::type>(std::begin(r), std::end(r));
}
#endif

#undef SROOK_BOYER_MOORE_HORSPOOL_CONCEPTS_ITERATOR

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
