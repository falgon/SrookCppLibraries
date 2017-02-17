#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_PARTITION
#define INCLUDED_SROOK_RANGE_ADAPTOR_PARTITION
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#if __has_include(<boost/range/algorithm/partition.hpp>)
#include<boost/range/algorithm/partition.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_PARTITION
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Predicate>
struct partition_t{
	template<REQUIRES(srook::is_callable_v<Predicate>)>
	explicit constexpr partition_t(Predicate pred):pred_(std::move(pred)){}

	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_PARTITION
		boost::range::partition(std::forward<Range>(r),std::move(pred_));
#else
		std::parition(r.begin(),r.end(),std::move(pred_));
#endif
	}
private:
	Predicate pred_;
};

template<class Predicate>
constexpr partition_t<std::decay_t<Predicate>> partition(Predicate&& pred)
{
	return partition_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::partition;

} // namespace pipealgo 
} // namespace srook

#endif
