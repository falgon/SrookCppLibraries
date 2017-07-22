// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_PUSH_HEAP_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_PUSH_HEAP_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

struct push_heap_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	Range&& operator()(Range&& r)
	{
		std::push_heap(r.begin(),r.end());
		return std::forward<Range>(r);	
	}
};

template<class Compare>
struct push_heap_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr push_heap_compare_t(Compare comp):comp_(std::move(comp)){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	Range&& operator()(Range&& r)
	{
		std::push_heap(r.begin(),r.end());
		return std::forward<Range>(r);
	}
private:
	Compare comp_;
};

constexpr push_heap_t push_heap()
{
	return push_heap_t();
}

template<class Compare>
constexpr push_heap_compare_t<std::decay_t<Compare>> push_heap(Compare&& comp)
{
	return push_heap_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::push_heap;

} // namespace pipealgo
} // namespace srook

#endif
