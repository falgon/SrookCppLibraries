// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_UPPER_BOUND_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_UPPER_BOUND_HPP
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class T>
struct upper_bound_t{
	explicit upper_bound_t(const T& value):value_(value){}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	auto operator()(Range&& r) -> decltype(std::begin(r))
	{
		return std::upper_bound(std::begin(r),std::end(r),value_);
	}
private:
	const T& value_;
};

template<class T,class Compare>
struct upper_bound_compare_t{
	template<
		REQUIRES(is_callable_v<std::remove_reference_t<std::remove_cv_t<Compare>>>)
	>
	explicit constexpr upper_bound_compare_t(const T& value,Compare compare)
		:value_(value),compare_(std::move(compare)){}
	
	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	auto operator()(Range&& r) -> decltype(std::begin(r))
	{
		return std::upper_bound(std::begin(r),std::end(r),value_,std::move(compare_));
	}
private:
	const T& value_;
	Compare compare_;
};

template<class T>
constexpr upper_bound_t<std::remove_reference_t<std::remove_cv_t<T>>>
upper_bound(T&& value)
{
	return upper_bound_t<
		std::remove_reference_t<std::remove_cv_t<T>>
	>(std::forward<T>(value));
}

template<
	class T,
	class Compare,
	REQUIRES(
			is_callable_v<std::remove_reference_t<std::remove_cv_t<Compare>>>
	)
>
constexpr upper_bound_compare_t<
	std::remove_reference_t<std::remove_cv_t<T>>,
	std::remove_reference_t<std::remove_cv_t<Compare>>
>
upper_bound(T&& value,Compare&& compare)
{
	return upper_bound_compare_t<
		std::remove_reference_t<std::remove_cv_t<T>>,
		std::remove_reference_t<std::remove_cv_t<Compare>>
	>(std::forward<T>(value),std::forward<Compare>(compare));
}

} // inline namespace v1
} // namespace detail

using detail::upper_bound;

} // namespace pipealgo
} // namespace srook

#endif
