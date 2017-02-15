#ifndef INLCLUDED_SROOK_RANGE_ADAPTOR_FIND_IF_HPP
#define INLCLUDED_SROOK_RANGE_ADAPTOR_FIND_IF_HPP
#include<utility>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>
namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Predicate>
struct find_if_t{
	template<REQUIRES(is_callable_v<Predicate>)>
	explicit constexpr find_if_t(const Predicate& pred):pred_(pred){}
	
	template<REQUIRES(is_callable_v<Predicate>)>
	explicit constexpr find_if_t(Predicate&& pred):pred_(std::move(pred)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return std::find_if(r.cbegin(),r.cend(),std::move(pred_));
	}
private:
	Predicate pred_;
};
template<class Predicate>
find_if_t<std::decay_t<Predicate>> find_if(Predicate&& pred)
{
	return find_if_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::find_if;

} // namespace adaptors
} // namespace srook

#endif
