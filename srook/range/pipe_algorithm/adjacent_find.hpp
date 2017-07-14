// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_ADJACENT_FIND_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_ADJACENT_FIND_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#if __has_include(<boost/range/algorithm/adjacent_find.hpp>)
#define POSSIBLE_TO_BOOST_ADJACENT_FIND
#include<boost/range/algorithm/adjacent_find.hpp>
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{

inline namespace v1{

template<class Predicate>
struct adjacent_find_t_predicate{
	explicit constexpr adjacent_find_t_predicate(const Predicate& pred):pred_(pred){}
	explicit constexpr adjacent_find_t_predicate(Predicate&& pred):pred_(std::move(pred)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_ADJACENT_FIND
		return boost::range::adjacent_find(std::forward<Range>(r),std::move(pred_));
#else
		return std::adjacent_find(r.cbegin(),r.cend(),std::move(pred_));
#endif
	}
private:
	Predicate pred_;
};
template<class Predicate>
constexpr adjacent_find_t_predicate<std::decay_t<Predicate>> adjacent_find(Predicate&& pred_)
{
	return adjacent_find_t_predicate<std::decay_t<Predicate>>(std::forward<Predicate>(pred_));
}

struct adjacent_find_t{
	template<class Range>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_ADJACENT_FIND
		return boost::range::adjacent_find(std::forward<Range>(r));
#else
		return std::adjacent_find(r.cbegin(),r.cend());
#endif
	}
};
constexpr adjacent_find_t adjacent_find()
{
	return adjacent_find_t();
}

} // inline namespace v1
} // namespace detail

using detail::adjacent_find;

} // namespace pipealgo
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_ADJACENT_FIND
#undef POSSIBLE_TO_BOOST_ADJACENT_FIND
#endif
#endif
