// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class ForwardIterator>
struct search_t{
	template<
		class Range,
		REQUIRES(
				!has_iterator_v<ForwardIterator> and
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
		)
	>
	explicit constexpr search_t(Range&& r)
		:first_(std::begin(r)),last_(std::end(r)){}

	template<
		REQUIRES(!has_iterator_v<ForwardIterator>)
	>
	explicit constexpr search_t(ForwardIterator first,ForwardIterator last)
		:first_(std::move(first)),last_(std::move(last)){}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	ForwardIterator operator()(Range&& r)
	{
		return std::search(std::begin(r),std::end(r),std::move(first_),std::move(last_));
	}
protected:
	ForwardIterator first_,last_;
};

template<class ForwardIterator,class Predicate>
struct search_pred_t final:search_t<ForwardIterator>{
	using search_t<ForwardIterator>::search_t;

	template<
		class Range,
		REQUIRES(
				!has_iterator_v<ForwardIterator>
				and
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
				and
				is_callable_v<Predicate>
		)
	>
	explicit constexpr search_pred_t(Range&& r,Predicate pred)
		:search_t<ForwardIterator>::search_t(std::forward<Range>(r)),pred_(std::move(pred)){}
	
	template<
		REQUIRES(
				!has_iterator_v<ForwardIterator>
				and
				is_callable_v<Predicate>
		)
	>
	explicit constexpr search_pred_t(ForwardIterator first,ForwardIterator last,Predicate pred)
		:search_t<ForwardIterator>::search_t(std::move(first),std::move(last)),pred_(std::move(pred)){}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	ForwardIterator operator()(Range&& r)
	{
		return std::search(std::begin(r),std::end(r),std::move(this->first_),std::move(this->last_),std::move(pred_));
	}
private:
	Predicate pred_;
};

template<
	class ForwardIterator,
	REQUIRES(!has_iterator_v<std::remove_reference_t<std::remove_cv_t<ForwardIterator>>>)
>
constexpr search_t<std::remove_reference_t<std::remove_cv_t<ForwardIterator>>>
search(ForwardIterator&& first,ForwardIterator&& last)
{
	return search_t<
		std::remove_reference_t<std::remove_cv_t<ForwardIterator>>
	>(std::forward<ForwardIterator>(first),std::forward<ForwardIterator>(last));
}

template<
	class Range,
	REQUIRES(
			has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or 
			is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
	)
>
constexpr search_t<typename std::remove_reference_t<std::remove_cv_t<Range>>::const_iterator>
search(Range&& r)
{
	return search_t<decltype(r.cbegin())>(std::forward<Range>(r));
}

template<
	class ForwardIterator,
	class Predicate,
	REQUIRES(
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<ForwardIterator>>>
			and
			is_callable_v<std::remove_reference_t<std::remove_cv_t<Predicate>>>
	)
>
constexpr search_pred_t<
	std::remove_reference_t<std::remove_cv_t<ForwardIterator>>,
	std::remove_reference_t<std::remove_cv_t<Predicate>>
>
search(ForwardIterator&& first,ForwardIterator&& last,Predicate&& pred)
{
	return search_pred_t<
		std::remove_reference_t<std::remove_cv_t<ForwardIterator>>,
		std::remove_reference_t<std::remove_cv_t<Predicate>>
	>(std::forward<ForwardIterator>(first),std::forward<ForwardIterator>(last),std::forward<Predicate>(pred));
}

template<
	class Range,
	class Predicate,
	REQUIRES(
			(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
			 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
			and
			is_callable_v<std::remove_reference_t<std::remove_cv_t<Predicate>>>
	)
>
constexpr search_pred_t<
	typename std::remove_reference_t<std::remove_cv_t<Range>>::const_iterator,
	std::remove_reference_t<std::remove_cv_t<Predicate>>
>
search(Range&& r,Predicate&& pred)
{
	return search_pred_t<
		decltype(r.cbegin()),
		std::remove_reference_t<std::remove_cv_t<Predicate>>
	>(std::forward<Range>(r),std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::search;

} // namesapce pipealgo
} // namespace srook
#endif
