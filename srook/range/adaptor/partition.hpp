#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_PARTITION
#define INCLUDED_SROOK_RANGE_ADAPTOR_PARTITION
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
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
		std::partition(r.begin(),r.end(),std::move(pred_));
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

} // namespace adaptors 
} // namespace srook

#endif
