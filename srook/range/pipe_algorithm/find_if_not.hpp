// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_FIND_IF_NOT
#define INCLUDED_SROOK_FIND_IF_NOT
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>

#if __has_include(<boost/range/algorithm/find_if_not.hpp>)
#include<boost/range/algorithm/find_if_not.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_FIND_IF_NOT
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Predicate>
struct find_if_not_t{
	template<REQUIRES(is_callable_v<Predicate>)>
	explicit constexpr find_if_not_t(Predicate pred):pred_(std::move(pred)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FIND_IF_NOT
		return boost::range::find_if_not(std::forward<Range>(r),std::move(pred_));
#else
		return std::find_if_not(r.cbegin(),r.cend(),std::move(pred_));
#endif
	}
private:
	Predicate pred_;
};

template<class Predicate>
constexpr find_if_not_t<std::decay_t<Predicate>> find_if_not(Predicate&& pred)
{
	return find_if_not_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::find_if_not;

} // namesapce pipealgo
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FIND_IF_NOT
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FIND_IF_NOT
#endif

#endif
