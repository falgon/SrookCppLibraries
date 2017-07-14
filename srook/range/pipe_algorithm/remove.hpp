// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_HPP
#include<srook/config/require.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/remove.hpp>)
#include<boost/range/algorithm/remove.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_REMOVE
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class T>
struct remove_t{
	explicit constexpr remove_t(const T& t):value_(t){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_REMOVE
		boost::range::remove(std::forward<Range>(r),std::move(value_));
#else
		return std::remove(r.begin(),r.end(),std::move(value_));
#endif
	}
private:
	T value_;
};

template<class T>
constexpr remove_t<std::decay_t<T>> remove(T&& value){return remove_t<std::decay_t<T>>(std::forward<T>(value));}

} // inline namespace v1
} // namespace detail

using detail::remove;

} // namespace pipealgo
} // namespace srook
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_REMOVE
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_REMOVE
#endif
#endif
