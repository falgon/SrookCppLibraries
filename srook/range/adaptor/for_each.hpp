#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_FOR_EACH
#define INCLUDED_SROOK_RANGE_ADAPTOR_FOR_EACH
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
struct for_each_t{
	template<REQUIRES(is_callable_v<Predicate>)>
	explicit constexpr for_each_t(Predicate pred):pred_(std::move(pred)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	auto operator()(Range&& r)
	{
		return std::for_each(r.begin(),r.end(),std::move(pred_));
	}
private:
	Predicate pred_;
};

template<class Predicate>
constexpr for_each_t<std::decay_t<Predicate>> for_each(Predicate&& pred)
{
	return for_each_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

}// inline namespace v1
}// namesapce detail

using detail::for_each;

}// namespace adaptors
}// namespace srook

#endif
