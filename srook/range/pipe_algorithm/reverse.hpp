// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REVERSE_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REVERSE_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
#if __has_include(<boost/range/algorithm/reverse.hpp>)
#include<boost/range/algorithm/reverse.hpp>
#define POSSIBLE_TO_INCLUDE_ALGORITHM_REVERSE
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

const struct reverse_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	constexpr std::decay_t<Range>& operator()(Range&& r)const
	{
#ifdef POSSIBLE_TO_INCLUDE_ALGORITHM_REVERSE
		boost::range::reverse(std::forward<Range>(r));
#else
		std::reverse(r.begin(),r.end());
#endif
		return r;
	}
}reverse={};


} // inline namespace v1
} // namespace detail

using detail::reverse;

} // namespace pipealgo
} // namesapce srook

#endif
