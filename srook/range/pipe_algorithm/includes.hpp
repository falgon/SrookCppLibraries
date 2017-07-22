// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_INCLUDES
#define INCLUDED_SROOK_RANGE_ADAPTOR_INCLUDES
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>

#include<algorithm>
#if __has_include(<boost/range/algorithm/set_algorithm.hpp>)
#include<boost/range/algorithm/set_algorithm.hpp>
#define POSSIBLE_TO_INCUDE_BOOST_RANGE_SET_ALGORITHM
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Range>
struct includes_t{
	template<REQUIRES(has_iterator_v<Range> || is_range_iterator_v<Range>)>
	explicit constexpr includes_t(const Range& r):r_(r){}

	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& range)const
	{
#ifdef POSSIBLE_TO_INCUDE_BOOST_RANGE_SET_ALGORITHM
		return boost::range::includes(std::forward<R>(range),r_);
#else
		return std::includes(range.cbegin(),range.cend(),r_.cbegin(),r_.cend());
#endif
	}
private:
	const Range& r_;
};
template<class Range,class Compare>
struct includes_compare_t{
	template<REQUIRES( (has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>) && is_callable_v<Compare> )>
	explicit constexpr includes_compare_t(const Range& r,Compare comp):r_(r),comp_(std::move(comp)){}

	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& range)
	{
#ifdef POSSIBLE_TO_INCUDE_BOOST_RANGE_SET_ALGORITHM
		return boost::range::includes(std::forward<R>(range),r_,std::move(comp_));
#else
		return std::includes(range.cbegin(),range.cend(),r_.cbegin(),r_.cend(),std::move(comp_));
#endif
	}
private:
	const Range& r_;
	Compare comp_;
};

template<class Iterator>
struct includes_iterator_t{
	template<REQUIRES(!has_iterator_v<Iterator> || is_range_iterator_v<Iterator>)>
	explicit constexpr includes_iterator_t(Iterator first,Iterator last):first_(std::move(first)),last_(std::move(last)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return std::includes(r.cbegin(),r.cend(),std::move(first_),std::move(last_));
	}
private:
	Iterator first_,last_;
};

template<class Iterator,class Compare>
struct includes_iterator_compare_t{
	template<REQUIRES( (!has_iterator_v<std::decay_t<Iterator>> || is_range_iterator_v<std::decay_t<Iterator>>) && is_callable_v<Compare> )>
	explicit constexpr includes_iterator_compare_t(Iterator first,Iterator last,Compare comp):first_(std::move(first)),last_(std::move(last)),comp_(std::move(comp)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return std::includes(r.cbegin(),r.cend(),std::move(first_),std::move(last_),std::move(comp_));
	}
private:
	Iterator first_,last_;
	Compare comp_;
};

template<class Range>
constexpr includes_t<std::decay_t<Range>> includes(Range&& r)
{
	return includes_t<std::decay_t<Range>>(std::forward<Range>(r));
}
template<class Range,class Compare>
constexpr includes_compare_t<std::decay_t<Range>,std::decay_t<Compare>> includes(Range&& r,Compare&& comp)
{
	return includes_compare_t<std::decay_t<Range>,std::decay_t<Compare>>(std::forward<Range>(r),std::forward<Compare>(comp));
}
template<class Iterator,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr includes_iterator_t<std::decay_t<Iterator>> includes(Iterator&& first,Iterator&& last)
{
	return includes_iterator_t<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}
template<class Iterator,class Compare>
constexpr includes_iterator_compare_t<std::decay_t<Iterator>,std::decay_t<Compare>> includes(Iterator&& first,Iterator&& last,Compare&& comp)
{
	return includes_iterator_compare_t<std::decay_t<Iterator>,std::decay_t<Compare>>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<Compare>(comp));
}

}// inline namespace v1
}// namespace detail

using detail::includes;

}// namespace pipealgo
}// namespace srook
#ifdef POSSIBLE_TO_INCUDE_BOOST_RANGE_SET_ALGORITHM
#undef POSSIBLE_TO_INCUDE_BOOST_RANGE_SET_ALGORITHM
#endif

#endif
