// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_PARTIAL_SORT_COPY
#define INCLUDED_SROOK_RANGE_ADAPTOR_PARTIAL_SORT_COPY
#if __has_include(<boost/range/algorithm/partial_sort_copy.hpp>)
#include<boost/range/algorithm/partial_sort_copy.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_PARTIAL_SORT_COPY
#else
#include<algorithm>
#endif
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Iterator>
struct partial_sort_copy_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator>)>
	explicit constexpr partial_sort_copy_t(Iterator first,Iterator last):first_(std::move(first)),last_(std::move(last)){}
 
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	Iterator operator()(Range&& r)
	{
		return std::partial_sort_copy(r.begin(),r.end(),std::move(first_),std::move(last_));
	}
private:
	Iterator first_,last_;
};


template<class Iterator,class Compare>
struct partial_sort_copy_compare_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator> && srook::is_callable_v<Compare>)>
	explicit constexpr partial_sort_copy_compare_t(Iterator first,Iterator last,Compare comp)
		:first_(std::move(first)),last_(std::move(last)),comp_(std::move(comp)){}

	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	Iterator operator()(Range&& r)
	{
		return std::partial_sort_copy(r.begin(),r.end(),std::move(first_),std::move(last_),std::move(comp_));
	}
private:
	Iterator first_,last_;
	Compare comp_;
};

template<class Range>
struct partial_sort_copy_range_t{
	template<REQUIRES(srook::mpl::has_iterator_v<Range> || is_range_iterator_v<std::decay_t<Range>>)>
	explicit constexpr partial_sort_copy_range_t(Range& r):r_(r){}

	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	typename std::decay_t<Range>::iterator operator()(R&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_PARTIAL_SORT_COPY
		boost::range::partial_sort_copy(std::forward<R>(r),r_);
#else
		std::partial_sort_copy(r.begin(),r.end(),r_.begin(),r_.end());
#endif
	}
private:
	Range& r_;
};

template<class Range,class Compare>
struct partial_sort_copy_range_compare_t{
	template<REQUIRES( (srook::mpl::has_iterator_v<Range> || is_range_iterator_v<std::decay_t<Range>>) && srook::is_callable_v<Compare>)>
	explicit constexpr partial_sort_copy_range_compare_t(Range& r,Compare comp):r_(r),comp_(std::move(comp)){}

	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	typename std::decay_t<Range>::iterator operator()(R&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_PARTIAL_SORT_COPY
		boost::range::partial_sort_copy(std::forward<R>(r),r_,std::move(comp_));
#else
		std::partial_sort_copy(r.begin(),r.end(),r_.begin(),r_.end(),std::move(comp_));
#endif
	}
private:
	Range& r_;
	Compare comp_;
};


template<class Iterator,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr partial_sort_copy_t<std::decay_t<Iterator>> partial_sort_copy(Iterator&& first,Iterator&& last)
{
	return partial_sort_copy_t<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}

template<class Iterator,class Compare,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>> && srook::is_callable_v<std::decay_t<Compare>>)>
constexpr partial_sort_copy_compare_t<std::decay_t<Iterator>,std::decay_t<Compare>> partial_sort_copy(Iterator&& first,Iterator&& last,Compare&& comp)
{
	return partial_sort_copy_compare_t<
		std::decay_t<Iterator>,
		std::decay_t<Compare>
	>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<Compare>(comp));
}

template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>>)>
constexpr partial_sort_copy_range_t<std::decay_t<Range>> partial_sort_copy(Range&& r)
{
	return partial_sort_copy_range_t<std::decay_t<Range>>(std::forward<Range>(r));
}

template<class Range,class Compare,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> && srook::is_callable_v<std::decay_t<Compare>>)>
constexpr partial_sort_copy_range_compare_t<std::decay_t<Range>,std::decay_t<Compare>> partial_sort_copy(Range&& r,Compare&& comp)
{
	return partial_sort_copy_range_compare_t<std::decay_t<Range>,std::decay_t<Compare>>(std::forward<Range>(r),std::forward<Compare>(comp));
}



} // inline namesapce v1
} // namespace detail

using detail::partial_sort_copy;

} // namespace pipealgo
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_PARTIAL_SORT_COPY
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_PARTIAL_SORT_COPY
#endif
#endif
