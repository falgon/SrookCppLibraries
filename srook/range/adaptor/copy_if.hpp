#ifndef INCLUDED_SROOK_ADAPTOR_COPY_IF
#define INCLUDED_SROOK_ADAPTOR_COPY_IF
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/copy_if.hpp>)
#define POSSIBLE_TO_BOOST_RANGE_COPY_IF
#include<boost/range/algorithm/copy_if.hpp>
#else
#include<algorithm>
#endif
namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator,class Predicate>
struct copy_if_t{
	explicit constexpr copy_if_t(Iterator iter,Predicate pred)
		:iter_(std::move(iter)),pred_(std::move(pred)){}
	template<class Range>
	srook::range_iterator<typename std::decay_t<Range>::const_iterator>
	operator ()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_RANGE_COPY_IF
		boost::copy_if(r,std::move(iter_),std::move(pred_));
#else
		std::copy_if(r.cbegin(),r.cend(),std::move(iter_),std::move(pred_));
#endif
		return make_range_iterator(r.cbegin(),r.cend());
	}
private:
	Iterator iter_;
	Predicate pred_;
};
template<class Iterator,class Predicate>
copy_if_t<std::decay_t<Iterator>,std::decay_t<Predicate>> copy_if(Iterator&& iter,Predicate&& pred)
{
	return copy_if_t<std::decay_t<Iterator>,std::decay_t<Predicate>>(std::forward<Iterator>(iter),std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::copy_if;

} // namespace adaptors
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_RANGE_COPY_IF
#undef POSSIBLE_TO_BOOST_RANGE_COPY_IF
#endif
#endif
