// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SWAP_RANGES_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SWAP_RANGES_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class ForwardIterator>
struct swap_ranges_t{
	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	explicit constexpr swap_ranges_t(Range&& r)
		:first_(r.begin()){}

	template<
		REQUIRES(
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<ForwardIterator>>>
		)
	>
	explicit constexpr swap_ranges_t(ForwardIterator first)
		:first_(std::move(first)){}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	ForwardIterator operator()(Range&& r)
	{
		return std::swap_ranges(r.begin(),r.end(),std::move(first_));
	}
private:
	ForwardIterator first_;
};

template<
	class ForwardIterator,
	REQUIRES(!has_iterator_v<std::remove_reference_t<std::remove_cv_t<ForwardIterator>>>)
>
constexpr swap_ranges_t<std::remove_reference_t<std::remove_cv_t<ForwardIterator>>>
swap_ranges(ForwardIterator&& iter)
{
	return swap_ranges_t<
		std::remove_reference_t<std::remove_cv_t<ForwardIterator>>
	>(std::forward<ForwardIterator>(iter));
}

template<
	class Range,
	REQUIRES(
			has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
			is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
	)
>
constexpr swap_ranges_t<typename std::remove_reference_t<std::remove_cv_t<Range>>::iterator>
swap_ranges(Range&& r)
{
	return swap_ranges_t<
		typename std::remove_reference_t<std::remove_cv_t<Range>>::iterator
	>(std::forward<Range>(r));
}

} // inline namespace v1
} // namespace detail

using detail::swap_ranges;

} // namespace pipealgo
} // namespace srook

#endif
