#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_COUNT_IF
#define INCLUDED_SROOK_RANGE_ADAPTOR_COUNT_IF
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/range/algorithm/count.hpp>)
#define POSSIBLE_TO_BOOST_RANGE_COUNT_IF
#include<boost/range/algorithm/count_if.hpp>
#else
#include<iterator>
#include<algorithm>
#include<type_traits>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Predicate>
struct count_if_t{
	explicit constexpr count_if_t(Predicate t):pred_(std::move(t)){}
	template<class Range>
	typename std::iterator_traits<typename std::decay_t<Range>::iterator>::difference_type operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_RANGE_COUNT_IF
		return boost::range::count_if(std::forward<Range>(r),std::move(pred_));
#else
		return std::count_if(r.cbegin(),r.cend(),std::move(pred_));
#endif
	}
private:
	Predicate pred_;
};
template<class Predicate>
constexpr count_if_t<std::decay_t<Predicate>> count_if(Predicate&& t)
{
	return count_if_t<std::decay_t<Predicate>>(std::forward<Predicate>(t));
}

} // inline namespace
} // namespace detail

using detail::count_if;

} // namespace adaptors
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_RANGE_COUNT_IF
#undef POSSIBLE_TO_BOOST_RANGE_COUNT_IF
#endif
#endif
