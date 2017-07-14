// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MINMAX_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_MINMAX_HPP
#include<algorithm>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class T>
struct minmax_t{
	explicit constexpr minmax_t(T t):value(std::move(t)){}
	
	template<REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<T>>)>
	constexpr std::pair<const T&,const T&> operator()(const T& rhs){return std::minmax(rhs,std::move(value));}
private:
	T value;
};

template<class T,class Compare>
struct minmax_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr minmax_compare_t(T t,Compare comp):value(std::move(t)),comp_(std::move(comp)){}
	
	template<REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<T>>)>
	constexpr std::pair<const T&,const T&> operator()(const T& rhs)
	{
		return std::minmax(rhs,std::move(value),std::move(comp_));
	}
private:
	T value;
	Compare comp_;
};

struct minmax_range_t{
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	constexpr std::pair<typename std::decay_t<Range>::value_type,typename std::decay_t<Range>::value_type> operator()(Range&& r)
	{
		auto p = std::minmax_element(r.cbegin(),r.cend());
		return std::make_pair(*p.first,*p.second);
	}
};

template<class Compare>
struct minmax_range_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr minmax_range_compare_t(Compare comp):comp_(std::move(comp)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	constexpr std::pair<typename std::decay_t<Range>::value_type,typename std::decay_t<Range>::value_type> operator()(Range&& r)
	{
		auto p = std::minmax_element(r.cbegin(),r.cend(),std::move(comp_));
		return std::make_pair(*p.first,*p.second);
	}
private:
	Compare comp_;
};

template<class T,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<T>> && !srook::is_callable_v<std::decay_t<T>>)>
constexpr minmax_t<std::decay_t<T>> minmax(T&& t)
{
	return minmax_t<std::decay_t<T>>(std::forward<T>(t));
}

template<class T,class Compare,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<T>> && srook::is_callable_v<std::decay_t<Compare>>)>
constexpr minmax_compare_t<std::decay_t<T>,std::decay_t<Compare>> minmax(T&& t,Compare&& comp)
{
	return minmax_compare_t<std::decay_t<T>,std::decay_t<Compare>>(std::forward<T>(t),std::forward<Compare>(comp));
}

constexpr minmax_range_t minmax()
{
	return minmax_range_t();
}

template<class Compare,REQUIRES(srook::is_callable_v<std::decay_t<Compare>>)>
constexpr minmax_range_compare_t<std::decay_t<Compare>> minmax(Compare&& comp)
{
	return minmax_range_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namesapce v1
} // namesapce detail

using detail::minmax;

} // namespace pipealgo
} // namespace srook
#endif
