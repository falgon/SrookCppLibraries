#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REVERSE_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REVERSE_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

const struct reverse_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	constexpr std::decay_t<Range>& operator()(Range&& r)const
	{
		std::reverse(r.begin(),r.end());
		return r;
	}
}reverse={};


} // inline namespace v1
} // namespace detail

using detail::reverse;

} // namespace adaptors
} // namesapce srook

#endif
