#ifndef INCLUDED_SROOK_ADAPTOR_COPY_BACKWARD
#define INCLUDED_SROOK_ADAPTOR_COPY_BACKWARD
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/copy_backward.hpp>)
#define POSSIBLE_TO_BOOST_RANGE_COPY_BACKWARD
#include<boost/range/algorithm/copy_backward.hpp>
#else
#include<algorithm>
#endif
namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Iterator>
struct copy_backward_t{
	explicit constexpr copy_backward_t(Iterator iter)
		:iter_(std::move(iter)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	auto operator ()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_RANGE_COPY_BACKWARD
		boost::copy_backward(r,std::move(iter_));
#else
		std::copy_backward(r.begin(),r.end(),std::move(iter_));
#endif
		return make_range_iterator(r.begin(),r.end());
	}
private:
	Iterator iter_;
};
template<class Iterator>
copy_backward_t<std::decay_t<Iterator>> copy_backward(Iterator&& iter)
{
	return copy_backward_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

} // inline namespace v1
} // namespace detail

using detail::copy_backward;

} // namespace pipealgo
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_RANGE_COPY_BACKWARD
#undef POSSIBLE_TO_BOOST_RANGE_COPY_BACKWARD
#endif
#endif
