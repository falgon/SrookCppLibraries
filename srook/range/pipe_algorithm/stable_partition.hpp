// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_STABLE_PARTITION_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_STABLE_PARTITION_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Predicate>
struct stable_partition_t{
	template<REQUIRES(is_callable_v<Predicate>)>
	explicit constexpr stable_partition_t(Predicate pred):pred_(std::move(pred)){}

	template<
		class Range,
		REQUIRES(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
	>
	typename std::remove_reference_t<std::remove_cv_t<Range>>::iterator
	operator()(Range&& r)
	{
		return std::stable_partition(r.begin(),r.end(),std::move(pred_));
	}
private:
	Predicate pred_;
};

template<class Predicate,REQUIRES(is_callable_v<std::remove_reference_t<std::remove_cv_t<Predicate>>>)>
constexpr stable_partition_t<std::remove_reference_t<std::remove_cv_t<Predicate>>> stable_partition(Predicate&& pred)
{
	return stable_partition_t<std::remove_reference_t<std::remove_cv_t<Predicate>>>(std::move(pred));
}

} // inline namespace v1
} // namespace detail

using detail::stable_partition;

} // namespace pipealgo
} // namespace srook

#endif
