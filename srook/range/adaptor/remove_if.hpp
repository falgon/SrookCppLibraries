#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_IF_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_IF_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Predicate>
struct remove_if_t{
	template<REQUIRES(is_callable_v<Predicate>)>
	explicit constexpr remove_if_t(Predicate pred):pred_(std::move(pred)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::iterator operator()(Range&& r)
	{
		return
		std::remove_if(r.begin(),r.end(),std::move(pred_));
	}
private:
	Predicate pred_;
};

template<class Predicate>
constexpr remove_if_t<std::decay_t<Predicate>> remove_if(Predicate&& pred)
{
	return remove_if_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::remove_if;

} // namespace adaptors
} // namespace srook 

#endif
