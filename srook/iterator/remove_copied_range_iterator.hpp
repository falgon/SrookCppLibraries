#ifndef INCLUDED_SROOK_REMOVE_COPIED_RANGE_ITERATOR_HPP
#define INCLUDED_SROOK_REMOVE_COPIED_RANGE_ITERATOR_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
#include<srook/iterator/skipping_iterator_value_core.hpp>

namespace srook{
inline namespace v1{

namespace{
	const auto skipper=[](auto&& first,auto&& last,const auto& x)
	{
		while(x==*first && first!=last)++first;
	};
}

template<class Iterator,class T,class Predicate>
struct remove_copied_range_iterator final:skipping_iterator_value_core<Iterator,T,Predicate>{
	using skipping_iterator_value_core<Iterator,T,Predicate>::skipping_iterator_value_core;
};

template<class Iterator,class T>
constexpr remove_copied_range_iterator<std::decay_t<Iterator>,std::decay_t<T>,decltype(skipper)>
make_remove_copied_range_iterator(Iterator&& first,Iterator&& last,T&& t)
{
	return remove_copied_range_iterator<
		std::decay_t<Iterator>,
		std::decay_t<T>,
		decltype(skipper)
	>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<T>(t),std::move(skipper));
}

} // inline namespace v1
} // namespace srook

#endif
