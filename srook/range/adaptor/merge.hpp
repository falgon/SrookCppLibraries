#ifndef SROOK_INCLUDED_RANGE_ADAPTOR_MERGE_HPP
#define SROOK_INCLUDED_RANGE_ADAPTOR_MERGE_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<algorithm>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/merge.hpp>)
#include<boost/range/algorithm/merge.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_MERGE
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Range,class OutputIterator>
struct merge_range_t{
	template<REQUIRES( (has_iterator_v<Range> || is_range_iterator_v<Range>) && !has_iterator_v<OutputIterator> )>
	explicit constexpr merge_range_t(const Range& r,OutputIterator oiter):r_(r),oiter_(std::move(oiter)){}

	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	OutputIterator operator()(R&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MERGE
		boost::range::merge(std::forward<R>(r),r_,std::move(oiter_));
#else
		std::merge(r.begin(),r.end(),r_.cbegin(),r_.cend(),std::move(oiter_));
#endif
	}
private:
	const Range& r_;
	OutputIterator oiter_;
};

template<class Iterator,class OutputIterator>
struct merge_iterator_t{
	template<REQUIRES( (!has_iterator_v<Iterator> || is_range_iterator_v<Iterator>) &&  !has_iterator_v<OutputIterator> )>
	explicit constexpr merge_iterator_t(Iterator first,Iterator last,OutputIterator oiter):first_(std::move(first)),last_(std::move(last)),oiter_(std::move(oiter)){}
	
	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	OutputIterator operator()(R&& r)
	{
		return std::merge(r.begin(),r.end(),std::move(first_),std::move(last_),std::move(oiter_));
	}
private:
	Iterator first_,last_;
	OutputIterator oiter_;
};

template<class Range,class OutputIterator,class Compare>
struct merge_range_compare_t{
	template<REQUIRES( (has_iterator_v<Range> || is_range_iterator_v<Range>) && !has_iterator_v<OutputIterator> && is_callable_v<Compare>)>
	explicit constexpr merge_range_compare_t(const Range& r,OutputIterator oiter,Compare comp):r_(r),oiter_(std::move(oiter)),comp_(std::move(comp)){}
	
	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	OutputIterator operator()(R&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MERGE
		boost::range::merge(std::forward<R>(r),r_,std::move(oiter_),std::move(comp_));
#else
		std::merge(r.begin(),r.end(),r_.cbegin(),r_.cend(),std::move(oiter_),std::move(comp_));
#endif
	}
private:
	const Range& r_;
	OutputIterator oiter_;
	Compare comp_;
};

template<class Iterator,class OutputIterator,class Compare>
struct merge_iterator_compare_t{
	template<REQUIRES( (!has_iterator_v<Iterator> || is_range_iterator_v<std::decay_t<Iterator>>) && !has_iterator_v<OutputIterator> && is_callable_v<Compare> )>
	explicit constexpr merge_iterator_compare_t(Iterator first,Iterator last,OutputIterator oiter,Compare comp)
		:first_(std::move(first)),last_(std::move(last)),oiter_(std::move(oiter)),comp_(std::move(comp)){}
	
	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	OutputIterator operator()(R&& r)
	{
		return std::merge(r.begin(),r.end(),std::move(first_),std::move(last_),std::move(oiter_),std::move(comp_));
	}
private:
	Iterator first_,last_;
	OutputIterator oiter_;
	Compare comp_;
};

template<
	class Range,
	class OutputIterator,
	REQUIRES( (srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>) && !has_iterator_v<std::decay_t<OutputIterator>>)
>
constexpr merge_range_t<std::decay_t<Range>,std::decay_t<OutputIterator>> merge(Range&& r,OutputIterator&& oiter)
{
	return merge_range_t<std::decay_t<Range>,std::decay_t<OutputIterator>>(std::forward<Range>(r),std::forward<OutputIterator>(oiter));
}

template<
	class Iterator,
	class OutputIterator,
	REQUIRES(
			!srook::mpl::has_iterator_v<std::decay_t<Iterator>> &&
			!has_iterator_v<std::decay_t<OutputIterator>>
	)
>
constexpr merge_iterator_t<std::decay_t<Iterator>,std::decay_t<OutputIterator>> merge(Iterator&& first,Iterator&& last,OutputIterator&& oiter)
{
	return merge_iterator_t<
		std::decay_t<Iterator>,
		std::decay_t<OutputIterator>
	>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<OutputIterator>(oiter));
}

template<
	class Range,
	class OutputIterator,
	class Compare,
	REQUIRES( 
			(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_callable_v<std::decay_t<Range>>) &&
			!has_iterator_v<std::decay_t<OutputIterator>> &&
			is_callable_v<std::decay_t<Compare>>
	)
>
constexpr merge_range_compare_t<std::decay_t<Range>,std::decay_t<OutputIterator>,std::decay_t<Compare>> merge(Range&& r,OutputIterator&& oiter,Compare&& comp)
{
	return merge_range_compare_t<
		std::decay_t<Range>,
		std::decay_t<OutputIterator>,
		std::decay_t<Compare>
	>(std::forward<Range>(r),std::forward<OutputIterator>(oiter),std::forward<Compare>(comp));
}

template<
	class Iterator,
	class OutputIterator,
	class Compare,
	REQUIRES(
			!srook::mpl::has_iterator_v<std::decay_t<Iterator>> && 
			!has_iterator_v<std::decay_t<OutputIterator>> &&
			is_callable_v<std::decay_t<Compare>>
	)
>
constexpr merge_iterator_compare_t<std::decay_t<Iterator>,std::decay_t<OutputIterator>,std::decay_t<Compare>>
merge(Iterator&& first,Iterator&& last,OutputIterator&& oiter,Compare&& comp)
{
	return merge_iterator_compare_t<
		std::decay_t<Iterator>,
		std::decay_t<OutputIterator>,
		std::decay_t<Compare>
	>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<OutputIterator>(oiter),std::forward<Compare>(comp));
}

} // inline namesapce v1
} // namespace detail

using detail::merge;

} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MERGE
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MERGE
#endif
#endif
