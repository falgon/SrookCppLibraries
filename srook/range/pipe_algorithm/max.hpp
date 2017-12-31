// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MAX_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_MAX_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<initializer_list>
#include<type_traits>
#include<srook/type_traits/is_callable.hpp>

#if __has_include(<boost/range/algorithm/max_element.hpp>)
#include<boost/range/algorithm/max_element.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAX_ELEMENT
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{


template<class T>
struct max_t{
	explicit constexpr max_t(T t):value(std::move(t)){}
	const T& operator()(const T& rhs)
	{
		return std::max(rhs,std::move(value));
	}
private:
	T value;
};

template<class T,class Compare>
struct max_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr max_compare_t(T t,Compare comp):value(std::move(t)),comp_(std::move(comp)){}
	const T& operator()(const T& rhs)
	{
		return std::max(rhs,std::move(value),std::move(comp_));
	}
private:
	T value;
	Compare comp_;
};

struct max_initializer_list_t{
	template<class T>
	T operator()(std::initializer_list<T> ilist)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAX_ELEMENT
		*boost::range::max_element(std::move(ilist));
#else
		*std::max_element(ilist.begin(),ilist.end());
#endif
	}
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::value_type operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAX_ELEMENT
		*boost::range::max_element(std::move(r));
#else
		*std::max_element(r.cbegin(),r.cend());
#endif
	}
};

template<class Compare>
struct max_initializer_list_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr max_initializer_list_compare_t(Compare comp):comp_(std::move(comp)){}
	template<class T>
	T operator()(std::initializer_list<T> ilist)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAX_ELEMENT
		*boost::range::max_element(std::move(ilist),std::move(comp_));
#else
		*std::max_element(ilist.begin(),ilist.end(),std::move(comp_));
#endif
	}
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::value_type operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAX_ELEMENT
		*boost::range::max_element(std::move(r),std::move(comp_));
#else
		*std::max_element(r.cbegin(),r.cend(),std::move(comp_));
#endif
	}
private:
	Compare comp_;
};

template<class T,REQUIRES(!srook::is_callable_v<std::decay_t<T>>)>
constexpr max_t<std::decay_t<T>> max(T&& t)
{
	return max_t<std::decay_t<T>>(std::forward<T>(t));
}

template<class T,class Compare,REQUIRES(srook::is_callable_v<std::decay_t<Compare>>)>
constexpr max_compare_t<std::decay_t<T>,std::decay_t<Compare>> max(T&& t,Compare&& comp)
{
	return max_compare_t<std::decay_t<T>,std::decay_t<Compare>>(std::forward<T>(t),std::forward<Compare>(comp));
}

constexpr max_initializer_list_t max()
{
	return max_initializer_list_t();
}

template<
	class Compare,
	REQUIRES( (std::is_function<std::decay_t<Compare>>::value && std::is_pointer<std::decay_t<Compare>>::value) || srook::is_callable_v<std::decay_t<Compare>> )
>
constexpr max_initializer_list_compare_t<std::decay_t<Compare>> max(Compare&& comp)
{
	return max_initializer_list_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // namespace v1
} // namesapce detail

using detail::max;

} // namespace pipealgo
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAX_ELEMENT
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAX_ELEMENT
#endif
#endif
