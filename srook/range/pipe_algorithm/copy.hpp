#ifndef INCLUDED_SROOK_ADAPTOR_COPY
#define INCLUDED_SROOK_ADAPTOR_COPY
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#if __has_include(<boost/range/algorithm/copy.hpp>)
#define POSSIBLE_TO_BOOST_RANGE_COPY
#include<boost/range/algorithm/copy.hpp>
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Iterator>
struct copy_t{
	explicit constexpr copy_t(Iterator iter)
		:iter_(std::move(iter)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	auto operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_RANGE_COPY
		boost::copy(r,std::move(iter_));
#else
		std::copy(r.begin(),r.end(),std::move(iter_));
#endif
		return make_range_iterator(r.begin(),r.end());
	}
private:
	Iterator iter_;
};
template<class Iterator>
copy_t<std::decay_t<Iterator>> copy(Iterator&& iter)
{
	return copy_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

} // inline namespace v1
} // namespace detail

using detail::copy;

} // namespace pipealgo
} // namespace srook

#ifdef POSSIBLE_TO_BOOST_RANGE_COPY
#undef POSSIBLE_TO_BOOST_RANGE_COPY
#endif
#endif
