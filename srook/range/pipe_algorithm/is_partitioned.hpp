// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_IS_PARTITIONED_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_IS_PARTITIONED_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Predicate>
struct is_partitioned_t{
	template<REQUIRES(is_callable_v<Predicate>)>
	explicit constexpr is_partitioned_t(Predicate pred):pred_(std::move(pred)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return std::is_partitioned(r.cbegin(),r.cend(),std::move(pred_));
	}
private:
	Predicate pred_;
};

template<class Predicate>
constexpr is_partitioned_t<std::decay_t<Predicate>> is_partitioned(Predicate&& pred)
{
	return is_partitioned_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::is_partitioned;

} // namespace pipealgo
} // namespace srook

#endif
