#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_COUNT_IF
#define INCLUDED_SROOK_RANGE_ADAPTOR_COUNT_IF
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<iterator>
#include<algorithm>
#include<type_traits>

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
		return std::count_if(r.cbegin(),r.cend(),std::move(pred_));
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
#endif
