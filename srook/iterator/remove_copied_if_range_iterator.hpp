#ifndef INCLUDED_SROOK_ITERATOR_REMOVE_COPIED_IF_HPP
#define INCLUDED_SROOK_ITERATOR_REMOVE_COPIED_IF_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
#include<srook/iterator/skipping_iterator_functor_core.hpp>

namespace srook{
inline namespace v1{

namespace{
	const auto skipper=[](auto&& first,auto&& last,const auto& pred)
	{
		while(pred(*first) && first!=last)++first;
	};
}

template<class Iterator,class Predicate,class Skipper>
struct remove_copied_if_range_iterator:skipping_iterator_functor_core<Iterator,Predicate,Skipper>{
	using skipping_iterator_functor_core<Iterator,Predicate,Skipper>::skipping_iterator_functor_core;
};

template<class Iterator,class T>
constexpr remove_copied_if_range_iterator<std::decay_t<Iterator>,std::decay_t<T>,decltype(skipper)>
make_remove_copied_if_range_iterator(Iterator&& first,Iterator&& last,T&& t)
{
	return remove_copied_if_range_iterator<
		std::decay_t<Iterator>,
		std::decay_t<T>,
		decltype(skipper)
	>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<T>(t),std::move(skipper));
}

} // inline namespace v1
} // namespace srook

#endif
