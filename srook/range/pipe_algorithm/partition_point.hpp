#ifndef INCLUDED_SROOK_RANGE_ITERATOR_PARTITION_POINT
#define INCLUDED_SROOK_RANGE_ITERATOR_PARTITION_POINT
#include<algorithm>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Predicate>
struct partition_point_t{
	template<REQUIRES(srook::is_callable_v<Predicate>)>
	explicit constexpr partition_point_t(Predicate pred):pred_(pred){}

	template<class Range,REQUIRES(srook::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return std::partition_point(r.cbegin(),r.cend(),std::move(pred_));
	}
private:
	Predicate pred_;
};

template<class Predicate>
constexpr partition_point_t<std::decay_t<Predicate>> partition_point(Predicate&& pred)
{
	return partition_point_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}


} // inline namesapce v1
} // namespace detail

using detail::partition_point;

} // namespace pipealgo
} // namespace srook

#endif
