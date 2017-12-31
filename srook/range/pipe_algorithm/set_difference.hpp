// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SET_DIFFERENCE_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SET_DIFFERENCE_HPP
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class InputIterator,class OutputIterator>
struct set_difference_t{
	template<REQUIRES(!has_iterator_v<InputIterator> and !has_iterator_v<OutputIterator>)>
	explicit constexpr set_difference_t(InputIterator first,InputIterator last,OutputIterator oiter)
		:first_(std::move(first)),last_(std::move(last)),oiter_(std::move(oiter)){}

	template<
		class Range,
		REQUIRES(
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
				and
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<InputIterator>>>
				and
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
		)
	>
	explicit constexpr set_difference_t(Range&& r,OutputIterator oiter)
		:first_(std::begin(r)),last_(std::end(r)),oiter_(std::move(oiter)){}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	OutputIterator operator()(Range&& r)
	{
		return std::set_difference(r.begin(),r.end(),std::move(first_),std::move(last_),std::move(oiter_));
	}
protected:
	InputIterator first_,last_;
	OutputIterator oiter_;
};

template<class InputIterator,class OutputIterator,class Compare>
struct set_difference_compare_t final:set_difference_t<InputIterator,OutputIterator>{
	using set_difference_t<InputIterator,OutputIterator>::set_difference_t;

	template<
		REQUIRES(!has_iterator_v<InputIterator> and !has_iterator_v<OutputIterator> and is_callable_v<Compare>)
	>
	explicit constexpr 
	set_difference_compare_t(InputIterator first,InputIterator last,OutputIterator oiter,Compare comp)
		:set_difference_t<InputIterator,OutputIterator>::set_difference_t(
				std::move(first),std::move(last),std::move(oiter)
		),
		comp_(std::move(comp))
	{}

	template<
		class Range,
		REQUIRES(
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
				and
				!has_iterator_v<InputIterator>
				and
				!has_iterator_v<OutputIterator>
				and
				is_callable_v<Compare>
		)
	>
	explicit constexpr
	set_difference_compare_t(Range&& r,OutputIterator oiter,Compare comp)
		:set_difference_t<InputIterator,OutputIterator>::set_difference_t(r.begin(),r.end(),std::move(oiter)),
		comp_(std::move(comp))
	{}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	OutputIterator operator()(Range&& r)
	{
		return std::set_difference(
				r.begin(),r.end(),std::move(this->first_),std::move(this->last_),std::move(this->oiter_),std::move(comp_)
		);
	}
private:
	Compare comp_;
};

template<
	class InputIterator,
	class OutputIterator,
	REQUIRES(
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<InputIterator>>> and
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
	)
>
constexpr set_difference_t<
	std::remove_reference_t<std::remove_cv_t<InputIterator>>,
	std::remove_reference_t<std::remove_cv_t<OutputIterator>>
>
set_difference(InputIterator first,InputIterator last,OutputIterator oiter)
{
	return set_difference_t<
		std::remove_reference_t<std::remove_cv_t<InputIterator>>,
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>
	>(std::forward<InputIterator>(first),std::forward<InputIterator>(last),std::forward<OutputIterator>(oiter));
}

template<
	class Range,
	class OutputIterator,
	REQUIRES(
			(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
			 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
			and
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
	)
>
constexpr set_difference_t<
	typename std::remove_reference_t<std::remove_cv_t<Range>>::iterator,
	std::remove_reference_t<std::remove_reference_t<OutputIterator>>
>
set_difference(Range&& r,OutputIterator oiter)
{
	return set_difference_t<
		typename std::remove_reference_t<std::remove_cv_t<Range>>::const_iterator,
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>
	>(std::forward<Range>(r),std::forward<OutputIterator>(oiter));
}

template<
	class InputIterator,
	class OutputIterator,
	class Compare,
	REQUIRES(
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<InputIterator>>> and
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>> and
			is_callable_v<std::remove_reference_t<std::remove_cv_t<Compare>>>
	)
>
constexpr set_difference_compare_t<
	std::remove_reference_t<std::remove_cv_t<InputIterator>>,
	std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
	std::remove_reference_t<std::remove_cv_t<Compare>>
>
set_difference(InputIterator&& first,InputIterator&& last,OutputIterator oiter,Compare&& comp)
{
	return set_difference_compare_t<
		std::remove_reference_t<std::remove_cv_t<InputIterator>>,
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
		std::remove_reference_t<std::remove_cv_t<Compare>>
	>(
			std::forward<InputIterator>(first),
			std::forward<InputIterator>(last),
			std::forward<OutputIterator>(oiter),
			std::forward<Compare>(comp)
	);
}

template<
	class Range,
	class OutputIterator,
	class Compare,
	REQUIRES(
			(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
			 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
			and
			!has_iterator_v<OutputIterator>
			and
			is_callable_v<Compare>
	)
>
constexpr set_difference_compare_t<
	typename std::remove_reference_t<std::remove_cv_t<Range>>::const_iterator,
	std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
	std::remove_reference_t<std::remove_cv_t<Compare>>
>
set_difference(Range&& r,OutputIterator&& oiter,Compare&& comp)
{
	return set_difference_compare_t<
		typename std::remove_reference_t<std::remove_cv_t<Range>>::const_iterator,
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
		std::remove_reference_t<std::remove_cv_t<Compare>>
	>(std::forward<Range>(r),std::forward<OutputIterator>(oiter),std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::set_difference;

} // namespace pipealgo
} // namespace srook

#endif
