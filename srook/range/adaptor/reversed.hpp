#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REVERSED_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REVERSED_HPP
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
namespace adaptors{
namespace detail{
inline namespace v1{

const struct reversed_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	constexpr range_iterator<std::reverse_iterator<typename std::decay_t<Range>::iterator>>
	operator()(Range&& r)const
	{
		return make_range_iterator(std::make_reverse_iterator(r.end()),std::make_reverse_iterator(r.begin()));
	}
}reversed={};

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

using detail::reversed;
using detail::reverse;

} // namespace adaptors
} // namesapce srook

#ifdef POSSIBLE_TO_INCLUDE_ALGORITHM_REVERSE
#undef POSSIBLE_TO_INCLUDE_ALGORITHM_REVERSE
#endif
#endif
