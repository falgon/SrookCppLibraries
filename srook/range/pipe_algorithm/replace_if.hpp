// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REPLACE_IF_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REPLACE_IF_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>
#if __has_include(<boost/range/algorithm/replace_if.hpp>)
#include<boost/range/algorithm/replace_if.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_ALGORITHM_REPLACE_IF
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Predicate,class T>
struct replace_if_t{
	template<REQUIRES(is_callable_v<Predicate>)>
	explicit constexpr replace_if_t(Predicate pred,const T& t):pred_(std::move(pred)),new_value(t){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	std::decay_t<Range>& operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_ALGORITHM_REPLACE_IF
		boost::range::replace_if(std::forward<Range>(r),std::move(pred_),new_value);
#else
		std::replace_if_t(r.begin(),r.end(),std::move(pred_),new_value);
#endif
	}
private:
	Predicate pred_;
	const T& new_value;
};

template<class Predicate,class T>
constexpr replace_if_t<std::decay_t<Predicate>,std::decay_t<T>> replace_if(Predicate&& pred,T&& t)
{
	return replace_if_t<std::decay_t<Predicate>,std::decay_t<T>>(std::forward<Predicate>(pred),std::forward<T>(t));
}

} // inline namespace v1
} // namespace detail

using detail::replace_if;

} // namespace pipealgo
} // namespace srook
#endif
