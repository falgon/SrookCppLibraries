// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_NONE_OF_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_NONE_OF_HPP
#include<algorithm>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Predicate>
struct none_of_t{
	template<REQUIRES(srook::is_callable_v<Predicate>)>
	explicit constexpr none_of_t(Predicate pred):pred_(std::move(pred)){}
	
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return none_of(r.cbegin(),r.cend(),std::move(pred_));
	}
private:
	Predicate pred_;
};

template<class Predicate>
constexpr none_of_t<std::decay_t<Predicate>> none_of(Predicate&& pred)
{
	return none_of_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namesapce detail

using detail::none_of;

} // namespace pipealgo
} // namespace srook

#endif
