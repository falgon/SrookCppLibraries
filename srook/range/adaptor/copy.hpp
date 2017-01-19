#ifndef INCLUDED_SROOK_ADAPTOR_COPY
#define INCLUDED_SROOK_ADAPTOR_COPY
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/copy.hpp>)
#define POSSIBLE_TO_BOOST_RANGE_COPY
#include<boost/range/algorithm/copy.hpp>
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
inline namespace v1{

template<class Iterator>
struct copy_t{
	explicit constexpr copy_t(Iterator iter)
		:iter_(std::move(iter)){}
	template<class Range>
	srook::range_iterator<typename std::decay_t<Range>::const_iterator>
	operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_RANGE_COPY
		boost::copy(std::forward<Range>(r),std::move(iter_));
#else
		std::copy(r.begin(),r.end(),std::move(iter_));
#endif
		return make_range_iterator(r.cbegin(),r.cend());
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
} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_BOOST_RANGE_COPY
#undef POSSIBLE_TO_BOOST_RANGE_COPY
#endif
#endif
