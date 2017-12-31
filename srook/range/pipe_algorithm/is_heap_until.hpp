// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTORS_IS_HEAP_UNTIL_HPP
#define INCLUDED_SROOK_RANGE_ADAPTORS_IS_HEAP_UNTIL_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#if __has_include(<boost/range/algorithm/is_heap_until.hpp>)
#include<boost/range/algorithm/is_heap_until.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_HEAP_UNTIL
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

struct is_heap_until_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_HEAP_UNTIL
		boost::range::is_heap_until(std::forward<Range>(r));
#else
		std::is_heap_until(r.cbegin(),r.cend());
#endif
	}
};

template<class Compare>
struct is_heap_until_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr is_heap_until_compare_t(Compare comp):comp_(std::move(comp)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_HEAP_UNTIL
		boost::range::is_heap_until(std::forward<Range>(r),std::move(comp_));
#else
		std::is_heap_until(r.cbegin(),r.cend(),std::move(comp_));
#endif
	}
private:
	Compare comp_;
};

constexpr is_heap_until_t is_heap_until()
{
	return is_heap_until_t();
}

template<class Compare>
constexpr is_heap_until_compare_t<std::decay_t<Compare>> is_heap_until(Compare&& comp)
{
	return is_heap_until_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::is_heap_until;

} // namespace pipealgo
} // namesapce srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_HEAP_UNTIL
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_HEAP_UNTIL
#endif
#endif
