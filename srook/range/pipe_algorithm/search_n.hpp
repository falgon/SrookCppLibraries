// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SEARCH_N_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SEARCH_N_HPP
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
struct search_n_t{
	explicit constexpr search_n_t(std::size_t size,const T& value)
		:size_(std::move(size)),value_(value){}
	
	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	auto operator()(Range&& r) -> decltype(std::begin(r))
	{
		return std::search_n(std::begin(r),std::end(r),size_,value_);
	}
protected:
	const std::size_t size_;
	const T& value_;
};

template<class T,class Predicate>
struct search_n_pred_t final:search_n_t<T>{
	using search_n_t<T>::search_n_t;

	explicit constexpr search_n_pred_t(std::size_t size,const T& value,Predicate pred)
			:search_n_t<T>::search_n_t(std::move(size),value),pred_(std::move(pred)){}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	auto operator()(Range&& r) -> decltype(std::begin(r))
	{
		return std::search_n(std::begin(r),std::end(r),this->size_,this->value_,std::move(pred_));
	}
private:
	Predicate pred_;
};

template<class T>
constexpr search_n_t<std::remove_reference_t<std::remove_cv_t<T>>>
search_n(std::size_t size,T&& t)
{
	return search_n_t<std::remove_reference_t<std::remove_cv_t<T>>>(std::move(size),std::forward<T>(t));
}

template<class T,class Predicate,REQUIRES(is_callable_v<std::remove_reference_t<std::remove_cv_t<Predicate>>>)>
constexpr search_n_pred_t<
	std::remove_reference_t<std::remove_cv_t<T>>,
	std::remove_reference_t<std::remove_cv_t<Predicate>>
>
search_n(std::size_t size,T&& t,Predicate pred)
{
	return search_n_pred_t<
		std::remove_reference_t<std::remove_cv_t<T>>,
		std::remove_reference_t<std::remove_cv_t<Predicate>>
	>(std::move(size),std::forward<T>(t),std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::search_n;

} // namespace pipealgo
} // namespace srook

#endif
