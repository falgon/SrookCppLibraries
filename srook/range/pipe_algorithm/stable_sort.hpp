// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_STABLE_SORT_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_STABLE_SORT_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

struct stable_sort_t{
	template<
		class Range,
		REQUIRES(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
	>
	Range&& operator()(Range&& r)
	{
		std::stable_sort(r.begin(),r.end());
		return std::forward<Range>(r);
	}
};

template<class Compare>
struct stable_sort_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr stable_sort_compare_t(Compare pred):pred_(std::move(pred)){}

	template<
		class Range,
		REQUIRES(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
	>
	Range&& operator()(Range&& r)
	{
		std::stable_sort(r.begin(),r.end(),std::move(pred_));
		return std::forward<Range>(r);
	}
private:
	Compare pred_;
};

constexpr stable_sort_t stable_sort(){return stable_sort_t();}

template<class Compare,REQUIRES(is_callable_v<std::remove_reference_t<std::remove_cv_t<Compare>>>)>
constexpr stable_sort_compare_t<std::remove_reference_t<std::remove_cv_t<Compare>>> stable_sort(Compare&& pred)
{
	return stable_sort_compare_t<std::remove_reference_t<std::remove_cv_t<Compare>>>(std::move(pred));
}

} // inline namespace v1
} // namespace detail

using detail::stable_sort;

} // namespace pipealgo
} // namespace srook

#endif
